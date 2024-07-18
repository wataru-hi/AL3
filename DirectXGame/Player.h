#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
//#include "MathUtilityForText.h"
class MapChipField;

struct collisionMapInfo
{
	bool ceiling;
	bool landing;
	bool hitWall;
	Vector3 move;
};

enum Corner {
	kRightBottom,//右下
	kLeftBottom,//左下
	kRightTop,//右上
	kLeftTop,//左上

	knumCount//要素数
};

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

	
	void InputMove();

	void CheckMapCollision(collisionMapInfo& info);

	const WorldTransform& GetWorldTransform() const{return worldTransform_;}

	const Vector3& GetVelocity()const{ return velocity_;}

	void setMapChipField(MapChipField* mapChipField){ mapChipField_ = mapChipField;}
private:
	
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t texturhandle_ = 0u;
	//ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;

	static inline const float kAttenuation = 0.05f;
	static inline const float kLimitRusSpeed = 0.5f;

	enum class LRDirection {
		kRight,
		kleft,
	};

	LRDirection lrDirection_ = LRDirection::kRight;

	Vector3 velocity_ = {};

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

	MapChipField* mapChipField_ = nullptr;

	static inline const float kWidth = 0.8f;
	static inline const float kHeight= 0.8f;

	
	//Vector3 CornerPosition(const Vector3& center, Corner corner);*/
};
