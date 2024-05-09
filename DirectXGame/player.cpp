#include <player.h>

///<summary>
/// 初期化
///<summary>
void Player::Initalize(Model* model, uint32_t taxturHandle, ViewProjection* viewProjection)
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

///<summary>
/// 更新
///<summary>
void Player::Update()
{
	worldTransform_.TransferMatrix();
}

///<summary>
/// 描画
///<summary>
void Player::Drow()
{
	model_->Draw(worldTransform_, *viewProjection_, texturhandle_);
}
