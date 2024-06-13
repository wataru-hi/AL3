#pragma once
#include <Vector3.h>
#include <assert.h>
#include <cmath>
#include "Matrix4x4.h"

Matrix4x4 add(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 Inverse(const Matrix4x4& m);
Matrix4x4 Transpose(const Matrix4x4& m);
Matrix4x4 MakeIdenttity4x4();
Matrix4x4 MakeTranslateMatrix(const Vector3& vector);
Matrix4x4 MakeScaleMatrix(const Vector3& vector);
Vector3 Transford(const Vector3& vector, const Matrix4x4& matrix);
Matrix4x4 MakeRoatateXMatix(float radian);
Matrix4x4 MakeRoatateYMatix(float radian);
Matrix4x4 MakeRoatateZMatix(float radian);
Matrix4x4 MakeRotateMatrix(const Vector3& radian);
