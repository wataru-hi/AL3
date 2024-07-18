#define NOMINMAX
#include <player.h>
#include <numbers>
#include "Input.h"
#include "MathUtilityForText.h"
#include <algorithm>

void checkmapCollisionUp(collisionMapInfo& info);
void checkmapCollisionDown(collisionMapInfo& info);
void checkmapCollisionLeft(collisionMapInfo& info);
void checkmapCollisionRight(collisionMapInfo& info);

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
	//worldTransform_.scale_ = {10.0f,10.0f,10.0f};


	worldTransform_.TransferMatrix();
	
	//引数の内容をメンバー変数に記録
	viewProjection_ = viewProjection;
}

///<summary>	
/// 更新
///<summary>
void Player::Update()
{

	InputMove();

	//衝突情報を初期化
	collisionMapInfo collisionMapInfo;
	//移動量に速度の値をコピー
	collisionMapInfo.move = velocity_;

	//振り向きアニメーション
	if(turnTimer_ > 0.0f)
	{
		//turnTimer_ -= 1.0f / 60.0f;
		turnTimer_ = std::max(turnTimer_ -(1.0f / 60.0f), 0.0f);

		float destionRotationYtable[] = {
			std::numbers::pi_v<float> / 2.0f,
			std::numbers::pi_v<float> *3.0f / 2.0f
		};
		//状態に応じた角度を取得する
		float destiationRotationY = destionRotationYtable[static_cast<uint32_t>(lrDirection_)];
					
		float time = turnTimer_ / kTimeTurn;

		//自キャラの角度を設定する
		float easeY = EaseInOut(destiationRotationY, turnFirstRotationY_, time);
		worldTransform_.rotation_.y = easeY;
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

void Player::InputMove()
{
	//着地フラグ
	bool landing = false;
	if (velocity_.y <= 0.0f)
	{
		if (worldTransform_.translation_.y <= groundHeight)
		{
			landing = true;
		}
	}

	// 移動入力
	if(onGround_)
	{

		// 左右移動操作
		if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT))
		{
			// 左右加速
			Vector3 acceleration = {};
			if (Input::GetInstance()->PushKey(DIK_RIGHT))
			{
				if (velocity_.x < 0.0f) {
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x += kAttenuation;
				if (lrDirection_ != LRDirection::kRight)
				{
					lrDirection_ = LRDirection::kRight;
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					turnTimer_ = kTimeTurn;
				}
			}
			else if (Input::GetInstance()->PushKey(DIK_LEFT))
			{
				if (velocity_.x > 0.0f) {
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x -= kAttenuation;
				if (lrDirection_ != LRDirection::kleft)
				{
					lrDirection_ = LRDirection::kleft;
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					turnTimer_ = kTimeTurn;

				}

			}
			velocity_ += acceleration;

			//最大速度制限
			velocity_.x = std::clamp(velocity_.x, -kLimitRusSpeed, kLimitRusSpeed);
		}
		else
		{
			velocity_.x *= (1.0f - kAttenuation);
		}

		if (Input::GetInstance()->PushKey(DIK_UP))
		{
			velocity_ += Vector3(0, kJumpAcceleciton, 0);
			if (velocity_.y > 0.0f)
			{
				onGround_ = false;
			}
		}	
	}
	else
	{
		//落下速度
		velocity_.y -= kGravityAcceleration;
		//落下速度制限
		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);

		if (landing)
		{
			worldTransform_.translation_.y = groundHeight;
			velocity_.x *= (1.0f - kAttenuation);
			velocity_.y = 0.0f;
			onGround_ = true;
		}
	}
}

void Player::checkmapCollision(collisionMapInfo& info)
{
	//移動後の4つの核の座標
	std::array<Vector3, 4> positionNew;

	for (uint32_t i = 0; i < positionNew.size(); ++i)
	{
		positionNew[i] = CornerPosition(worldTransform_.translation_ + info.move, static_cast<Corner>(i));
	}
}

Vector3 Player::CornerPosition(const Vector3& center, Corner corner)
{
	Vector3 offsetTable[4]
	{
		{+kWidth / 2.0f, -kHeight / 2.0f, 0},
		{-kWidth / 2.0f, -kHeight / 2.0f, 0},
		{+kWidth / 2.0f, +kHeight / 2.0f, 0},
		{-kWidth / 2.0f, +kHeight / 2.0f, 0}
	};

	return center + offsetTable[static_cast<uint32_t>(corner)];
}

void checkmapCollisionUp(collisionMapInfo& info)
{
	if (info.move.y <= 0)
	{
		return;
	}

}
