#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Mymath.h"

Vector3 Cross(const Vector3& v1, const Vector3& v2);

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

	Vector3 v1{1.2f, -3.9f, 2.5f};
	Vector3 v2{2.8f, 0.4f, -1.3f};
	Vector3 cross = Cross(v1,v2);
	Vector3 rotate ={0.0f};
	Vector3 translate ={0.0f};
	Vector3 cameraPos;


	// 各種行列の計算
	Matrix4x4 worldMatrix = MakeAffineMatrix({1.0f, 1.0f, 1.0f}, rotate, translate);
	Matrix4x4 cameraMatrix = MakeAffineMatrix({1.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, cameraPosition);
	Matrix4x4 viewMatrix = Inverse(cameraMatrix);
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, float(kwindowWidth) / float(kwindowHeight), 0.1f, 100.0f);
	Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
	Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kwindowwidth), float(kwindowHeight), 0.0f, 1.0f);

	Vector3 screenVertices[3];
	for (uint32 i = 0; i < 3; ++i) {
		Transform(kLocalvertices[i], worldViewProjectionMatrix);
		screenVertices[i] = Transform(ndcVertex, viewportMatrix);
		Vector3 ndcvertex;
	}

	// 画面に描画
	Novice::DrawTriangle(
		int(screenVertices[0].x), int(screenVertices[0].y),
		int(screenVertices[1].x), int(screenVertices[1].y),
		int(screenVertices[2].x), int(screenVertices[2].y),
		RED, kFillModeSolid
	);

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};

Vector3 Cross(const Vector3& v1, const Vector3& v2)
{
    struct Vector3 result;
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;
    return result;
}