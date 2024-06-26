#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete modelSkydome_;

	for(std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_){
		for(WorldTransform* worldTransBlock : worldTransformBlockLine){
		delete worldTransBlock;
		}
	}
	worldTransformBlocks_.clear();

	delete debugCamera_;

	//マップチップフィールドの開放
	delete mapChipField_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//３Dモデルの読み込み
	model_ = Model::CreateFromOBJ("player", true);
	blockModel_ = Model::Create();
	modelSkydome_ = Model::CreateFromOBJ("sphere", true);

	textureHandle_ = TextureManager::Load("player/player.png");

	//ビュープロジェクションの初期化
	viewProjection_.farZ = 1000.0f;
	viewProjection_.Initialize();

	mapChipField_ = new MapCHipField;
	mapChipField_->LoadMapChipCsv("Resources/map.csv");
	GenerateBlocks();

	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(1,18);
	//自キャラの生成
	player_ = new Player();
	//プレイヤーの初期化
	player_->Initalize(textureHandle_, &viewProjection_, playerPosition);

	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_, SkydometextureHandle_, &viewProjection_);

	

	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
}

void GameScene::Update() {
	player_->Update();

	for (std::vector<WorldTransform*> worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if(!worldTransformBlock)
				continue;

			//アフィン変換行列の作成
			worldTransformBlock->UpdateMatrix();
		}
	}

#ifdef _DEBUG
	if (input_->TriggerKey(DIK_Q))
	{
		if(isDebugCameraActive_)
		{
			isDebugCameraActive_ = false;
		}
		else {
			isDebugCameraActive_ = true;
		}	
	}
#endif // _DEBUG

	//カメラの処理
	if (isDebugCameraActive_)
	{
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	}
	else {
		viewProjection_.UpdateMatrix();
	}

	
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	//自キャラの描画
	player_->Drow();
	//skydome_->Draw();

	//ブロックの描画
	for(std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_){
		for(WorldTransform* worldTransBlock : worldTransformBlockLine){
			if (!worldTransBlock)
					continue;

			blockModel_->Draw(*worldTransBlock, viewProjection_);
		}
	}
	
	////縦横ブロック描画
	//for (std::vector<WorldTransform*> worldTransformBlockTate : worldTransformBlocks_) {
	//	for (WorldTransform* worldTransformBlockYoko : worldTransformBlockTate) {
	//		if (!worldTransformBlockYoko)
	//			continue;

	//		blockModel_->Draw(*worldTransformBlockYoko, viewProjection_);
	//	}
	//}
	
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::GenerateBlocks()
{
	//要素数
	uint32_t NumBlockVirtical = mapChipField_->GetNumBlockVirtical();
	uint32_t NumBlockHorizontal = mapChipField_->GetNumBlockHoraizontal();
	//要素数を変更する
	worldTransformBlocks_.resize(NumBlockVirtical);
	for (uint32_t i = 0; i < NumBlockVirtical; ++i)
	{
		worldTransformBlocks_[i].resize(NumBlockHorizontal);
	}

	//キューブの生成
	for (uint32_t i = 0; i < NumBlockVirtical; ++i){
		for (uint32_t j = 0; j < NumBlockHorizontal; ++j){
			if(mapChipField_->getMapChipType(j,i) == MapChipType::kblock)
			{
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j,i);
			}
		}
	}


}
