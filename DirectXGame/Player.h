#include <Model.h>
#include <WorldTransform.h>
class Player
{
public:
	///<summary>
	/// 初期化
	///<summary>
	void Initalize();

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
};