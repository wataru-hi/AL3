#include <Model.h>
#include <WorldTransform.h>
#include <cassert>
#include "ImGuiManager.h"
class Player
{
public:
	///<summary>
	/// 初期化
	///</summary>
	void Initalize(uint32_t taxturHandle, ViewProjection* viewProjection, const Vector3& position);

	///<summary>
	/// 更新
	///<summary>
	void Update();

	///<summary>
	/// 描画
	///<summary>
	void Drow();

	Vector3 velocity_ = {};
private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t texturhandle_ = 0u;
	//ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;

	static inline const float kAttenuation = 0.1f;
	static inline const float kLimitRusSpeed = 1.0f;

	enum class LRDirection {
		kRight,
		kleft,
	};

	LRDirection lrDirection_ = LRDirection::kRight;

	//旋回開始の角度
	float turnFirstRotationY_ = 0.0f;
	//旋回タイマー
	float turnTimer_ = 0.0f;
	//旋回時間
	static inline const float kTimeTurn = 0.3f;
	
	//着地状態
	bool onGround_ = true;
	//重力加速度(下方向)
	static inline const float kGravityAcceleration = 0.12f;
	//最大落下速度(下方向)
	static inline const float kLimitFallSpeed = 9.8f;
	//ジャンプ初速(上方向)
	static inline const float kJumpAcceleciton = 1.0f;

	//地面の高さ
	static inline const float groundHeight = 1.5f;
};