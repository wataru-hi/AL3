#include <Model.h>
#include <WorldTransform.h>
#include <cassert>
#include "ImGuiManager.h"
class Player
{
public:
	///<summary>
	/// 初期化
	///<summary>
	void Initalize(uint32_t taxturHandle, ViewProjection* viewProjection);

	///<summary>
	/// 更新
	///<summary>
	void Update();

	///<summary>
	/// 描画
	///<summary>
	void Drow();
private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t texturhandle_ = 0u;
	//ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
};