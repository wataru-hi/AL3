#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include "Player.h"
#include "Skydome.h"
#include <vector>
#include "DebugCamera.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
	//テクスチャハンドル
	uint32_t textureHandle_ = 0;
	uint32_t SkydometextureHandle_ = 0;

	//３Dモデル
	Model* model_ = nullptr;

	Model* blockModel_ = nullptr;

	Model* modelSkydome_ = nullptr;
	
	//ビュープロジェクション
	ViewProjection viewProjection_;

	//自キャラ
	Player* player_ = nullptr;
	Skydome* skydome_ = nullptr;

	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;


	//要素数
	const uint32_t kNumBlockVirtical = 10;
	const uint32_t kNumBlockHorizontal = 20;

	//デバッグカメラ
	bool isDebugCameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;
};
