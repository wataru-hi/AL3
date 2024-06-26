#define _USE_MATH_DEFINES
#include <cmath>
#include <numbers>
#include <Matrix4x4.h>
#include <Vector3.h>
Matrix4x4 MakeRoatateXMatix(float radian);
Matrix4x4 MakeRoatateYMatix(float radian);
Matrix4x4 MakeRoatateZMatix(float radian);

//行列の掛け算
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

Matrix4x4 MakeRotateMatrix(const Vector3& radian);
//アフィン変換行列作成
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
float EaseInOut(float x1, float x2, float t);
