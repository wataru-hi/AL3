#include "CameraContoroller.h"
#include "Player.h"	
#include "MathUtilityForText.h"
#include <algorithm>
//#include <cassert>
#include "ImGuiManager.h"

Vector3 targetOffset_ = { 0, 0, 15.0f};

void CameraContoroller::Initialize()
{
	//ビュープロジェクションの初期化
	viewProjection_.farZ = 1000.0f;
	viewProjection_.Initialize();
}

void CameraContoroller::Update()
{
	Vector3 targetVelocity = target_->GetVelocity();
	float cameraYLoc = viewProjection_.translation_.y;

	//追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	//追従対象とオフセットからカメラの目標座標を計算
	cameraTargetCoordinates = sumVector(sumVector(targetWorldTransform.translation_, targetOffset_), MultiplyVectorFloat(targetVelocity , kBelocityBias));
	//viewProjection_.translation_ = sumVector(targetWorldTransform.translation_, targetOffset_);

	viewProjection_.translation_ = Lerp(viewProjection_.translation_,cameraTargetCoordinates,kInterpolationRate);

	viewProjection_.translation_.x = std::clamp(viewProjection_.translation_.x, targetWorldTransform.translation_.x + cameraOrbit.left, targetWorldTransform.translation_.x + cameraOrbit.rigjt);
	//viewProjection_.translation_.y = std::clamp(viewProjection_.translation_.y, cameraOrbit.top, cameraOrbit.bottom);
	
	viewProjection_.translation_.x = std::clamp(viewProjection_.translation_.x,movableArea_.left,movableArea_.rigjt);
	viewProjection_.translation_.y = std::clamp(viewProjection_.translation_.y,movableArea_.bottom,movableArea_.top);
	
	viewProjection_.translation_.y = cameraYLoc;

	viewProjection_.UpdateMatrix();

	ImGui::Begin("a");

	ImGui::Text("%f,%f,%f viewPro", viewProjection_.translation_.x,viewProjection_.translation_.y, viewProjection_.translation_.z);
	ImGui::Text("%f,%f,%f 補完前", cameraTargetCoordinates.x,cameraTargetCoordinates.y, cameraTargetCoordinates.z);

	ImGui::End();
}

void CameraContoroller::Reset()
{
	//追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	//追従対象をオフセットからカメラの座標に変換
	viewProjection_.translation_ = sumVector(targetWorldTransform.translation_, targetOffset_);
	viewProjection_.UpdateMatrix();
}
