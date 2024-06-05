#include <Model.h>
#include <WorldTransform.h>
#include <cassert>
/// <summary>
/// 天球
/// </summary>
class Skydome
{

public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, uint32_t taxturHandle, ViewProjection* viewProjection);


	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t texturhandle_ = NULL;
	//ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
};