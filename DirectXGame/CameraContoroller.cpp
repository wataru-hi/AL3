#include "CameraContoroller.h"


void CameraContoroller::Initialize()
{
	//ビュープロジェクションの初期化
	viewProjection_.farZ = 1000.0f;
	viewProjection_.Initialize();
}

void CameraContoroller::Update()
{
}

void CameraContoroller::Reset()
{
	//追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->
}
