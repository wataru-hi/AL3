#include "ViewProjection.h"
#include "Player.h"
class Player;

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
private:
	//ビュープロジェクション
	ViewProjection viewProjection_;

	Player* target_ = nullptr;

	//追従対象とカメラ座標の差(オフセット)
	Vector3 targetOffset_ = {0.0f, 0.0f, -15.0f};
};