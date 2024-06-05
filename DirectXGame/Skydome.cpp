#include "Skydome.h"

void Skydome::Initialize(Model* model, uint32_t taxturHandle, ViewProjection* viewProjection)
{

	//nullポインタチェック
	assert(model);

	//引数として受け取ったデータをメンバー変数に記録する
	model_ = model;

	//ワールド変換の初期化
	worldTransform_.Initialize();
	texturhandle_ = taxturHandle;

	//引数の内容をメンバー変数に記録
	viewProjection_ = viewProjection;
}

void Skydome::Update()
{
	worldTransform_.TransferMatrix();
}

void Skydome::Draw()
{
	model_->Draw(worldTransform_, *viewProjection_, texturhandle_);
}
