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
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");

	//３Dモデルの読み込み
	model_ = Model::Create();
	blockModel_ = Model::Create();
	modelSkydome_ = Model::CreateFromOBJ("sphere", true);

	//ビュープロジェクションの初期化
	viewProjection_.farZ = 1000.0f;
	viewProjection_.Initialize();

	//自キャラの生成
	player_ = new Player();
	//プレイヤーの初期化
	player_->Initalize(model_, textureHandle_, &viewProjection_);

	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_, SkydometextureHandle_, &viewProjection_);

	//ブロック1個分の横幅
	const float kBlockHeigth = 2.0f;
	const float kBlockWidth = 2.0f;
	//要素数を変更する
	worldTransformBlocks_.resize(kNumBlockVirtical);
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i)
	{
		worldTransformBlocks_[i].resize(kNumBlockHorizontal);
	}

	//キューブの生成
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i){
		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j){	
			if ((i - j) % 2 == 0)
				continue;

			worldTransformBlocks_[i][j] = new WorldTransform();
			worldTransformBlocks_[i][j]->Initialize();
			worldTransformBlocks_[i][j]->translation_.x = kBlockWidth * j;
			worldTransformBlocks_[i][j]->translation_.y = kBlockHeigth * i;
		}
	}

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

//	// 縦横ブロック更新
//	for (std::vector<WorldTransform*> worldTransformBlockTate : worldTransformBlocks_) {
//		for (WorldTransform* worldTransformBlockYoko : worldTransformBlockTate) {
//			if (!worldTransformBlockYoko)
//				continue;
//
//			// アフィン変換行列の作成
//			worldTransformBlockYoko->UpdateMatrix();
//		}
//	}
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
	//player_->Drow();
	skydome_->Draw();

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
