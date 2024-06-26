#include <player.h>
#include <numbers>
#include "Input.h"
#include "MathUtilityForText.h"
#include <algorithm>

///<summary>
/// 初期化
///<summary>
void Player::Initalize(uint32_t taxturHandle, ViewProjection* viewProjection, const Vector3& position)
{
	model_ = Model::CreateFromOBJ("player", true);

	//nullポインタチェック
	assert(model_);

	//ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	texturhandle_ = taxturHandle;

	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;


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

	
	////移動
	//worldTransform_.translation_ += velocity_;

	// 移動入力
	// 左右移動強化
	if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT))
	{
		// 左右加速
		Vector3 acceleration = {};
		if (Input::GetInstance()->PushKey(DIK_RIGHT))
		{
			if (velocity_.x < 0.0f) {
				velocity_.x *= (1.0f - kAccelecition);
			}
			acceleration.x += kAccelecition;
			if (lrDirection_ != LRDirection::kRight)
			{
				lrDirection_ = LRDirection::kRight;
				worldTransform_.rotation_.y = turnFirstRotationY_;
				turnTimer_ = kTimeTurn;
				if(turnTimer_ > 0.0f)
				{
					turnTimer_ -= (1 / 60);
					float destionRotationYtable[] = {
						std::numbers::pi_v<float> / 2.0f,
						std::numbers::pi_v<float> *3.0f / 2.0f
					};
					//状態に応じた角度を取得する
					float destiationRotationY = destionRotationYtable[static_cast<uint32_t>(lrDirection_)];
					//自キャラの角度を設定する
					float easeRot = destiationRotationY * easeInOutSine(turnTimer_);
					Count++;
					worldTransform_.rotation_.y = easeRot;
				}
			}
		}
		else if (Input::GetInstance()->PushKey(DIK_LEFT))
		{
			if (velocity_.x > 0.0f) {
				velocity_.x *= (1.0f - kAccelecition);
			}
			acceleration.x -= kAccelecition;
			if (lrDirection_ != LRDirection::kleft)
			{
				lrDirection_ = LRDirection::kleft;
				worldTransform_.rotation_.y = turnFirstRotationY_;
				turnTimer_ = kTimeTurn;worldTransform_.rotation_.y = turnFirstRotationY_;
				turnTimer_ = kTimeTurn;
				if(turnTimer_ > 0.0f)
				{
					turnTimer_ -= 1 / 60;
					float destionRotationYtable[] = {
						std::numbers::pi_v<float> / 2.0f,
						std::numbers::pi_v<float> *3.0f / 2.0f
					};
					//状態に応じた角度を取得する
					float destiationRotationY = destionRotationYtable[static_cast<uint32_t>(lrDirection_)];
					//自キャラの角度を設定する
					worldTransform_.rotation_.y = destiationRotationY * easeInOutSine(turnTimer_);
				}
			}
		}
		velocity_ += acceleration;

		//最大速度制限
		velocity_.x = std::clamp(velocity_.x, -kLimitRusSpeed, kLimitRusSpeed);
	}
	else
	{
		velocity_.x *= (1.0f - kAccelecition);
	}

	// 移動
	worldTransform_.translation_ += velocity_;


	//行列計算
	worldTransform_.UpdateMatrix();
}

///<summary>
/// 描画
///<summary>
void Player::Drow()
{
	model_->Draw(worldTransform_, *viewProjection_, texturhandle_);
}
