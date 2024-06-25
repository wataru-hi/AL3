#include <player.h>

///<summary>
/// 初期化
///<summary>
void Player::Initalize(uint32_t taxturHandle, ViewProjection* viewProjection)
{
	model_ = Model::CreateFromOBJ("player", true);

	//nullポインタチェック
	assert(model_);

	taxturHandle = taxturHandle;
	
	//ワールド変換の初期化
	worldTransform_.Initialize();
	//texturhandle_ = taxturHandle;

	worldTransform_.TransferMatrix();
	
	//引数の内容をメンバー変数に記録
	viewProjection_ = viewProjection;
}

///<summary>
/// 更新
///<summary>
void Player::Update()
{
	ImGui::Begin("Debug1");
	ImGui::DragFloat("scaleX", &worldTransform_.scale_.x,0.1f,100.0f);
	ImGui::DragFloat("scaleY", &worldTransform_.scale_.y,0.1f,100.0f);
	ImGui::DragFloat("scaleZ", &worldTransform_.scale_.z,0.1f,100.0f);
	// Rotate
	ImGui::DragFloat("rotateX", &worldTransform_.rotation_.x, 0.1f, 0.0f, 360.0f);
	ImGui::DragFloat("rotateY", &worldTransform_.rotation_.y, 0.1f, 0.0f, 360.0f);
	ImGui::DragFloat("rotateZ", &worldTransform_.rotation_.z, 0.1f, 0.0f, 360.0f);
	// Translate
	ImGui::DragFloat("translateX", &worldTransform_.translation_.x, 0.1f);
	ImGui::DragFloat("translateY", &worldTransform_.translation_.y, 0.1f);
	ImGui::DragFloat("translateZ", &worldTransform_.translation_.z, 0.1f);
	ImGui::End();
	worldTransform_.UpdateMatrix();
}

///<summary>
/// 描画
///<summary>
void Player::Drow()
{
	model_->Draw(worldTransform_, *viewProjection_, texturhandle_);
}
