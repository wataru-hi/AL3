#include "ViewProjection.h"
//#include "Player.h"
class Player;

struct Rect {
	float left = 0.0f;
	float rigjt = 1.0f;
	float bottom = 0.0f;
	float top = 1.0f;
};

/// <summary>
/// カメラコントロール
/// </summary>
class CameraContoroller
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	void Reset();

	void SetTarget(Player* target){ target_ = target;};

	const ViewProjection& GetViewProjection() const{
		return viewProjection_;
	}

	void SetMovableArea(Rect Area){ movableArea_ = Area;};
private:
	//ビュープロジェクション
	ViewProjection viewProjection_;

	Player* target_ = nullptr;

	//追従対象とカメラ座標の差(オフセット)
	Vector3 targetOffset_ = {0.0f, 0.0f, -15.0f};

	//カメラ移動配列
	Rect movableArea_ = {0, 100, 0, 100};

	//カメラの目標座標
	Vector3 cameraTargetCoordinates;
	//座標補完割合
	static inline const float kInterpolationRate = 0.9f;

	//速度掛け率
	static inline const float kBelocityBias = 10.0f;

	//追従対象の後ろ方向へのカメラ移動範囲
	static inline const Rect cameraOrbit = {-1.0f, 1.0f, -10.0f, 10.0f};
};