#include <Mymath.h>

float Lerp(float x1, float x2, float t);
Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);

Matrix4x4 MakeRoatateXMatix(float radian)
{
	Matrix4x4 result = { 0.0f };

	result.m[0][0] = 1.0f;

	result.m[1][1] = std::cos(radian);
	result.m[1][2] = std::sin(radian);
	result.m[2][1] = std::sin(radian * -1);
	result.m[2][2] = std::cos(radian);

	result.m[3][3] = 1.0f;

	return result;
}

Matrix4x4 MakeRoatateYMatix(float radian)
{
	Matrix4x4 result = { 0.0f };

	result.m[1][1] = 1.0f;

	result.m[0][0] = cosf(radian);
	result.m[0][2] = -sinf(radian);
	result.m[2][0] = sinf(radian);
	result.m[2][2] = cosf(radian);

	result.m[3][3] = 1.0f;

	return result;
}

Matrix4x4 MakeRoatateZMatix(float radian)
{
	Matrix4x4 result = { 0.0f };

	result.m[2][2] = 1.0f;

	result.m[0][0] = cosf(radian);
	result.m[0][1] = sinf(radian);
	result.m[1][0] = -sinf(radian);
	result.m[1][1] = cosf(radian);

	result.m[3][3] = 1.0f;

	return result;
}

//行列の掛け算
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
   
    Matrix4x4 result;
  
    result.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] + m1.m[0][2] * m2.m[2][0] +
    m1.m[0][3] * m2.m[3][0];
    result.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] + m1.m[0][2] * m2.m[2][1] +
    m1.m[0][3] * m2.m[3][1];
    result.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] + m1.m[0][2] * m2.m[2][2] +
    m1.m[0][3] * m2.m[3][2];
    result.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] + m1.m[0][2] * m2.m[2][3] +
    m1.m[0][3] * m2.m[3][3];
    result.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] + m1.m[1][2] * m2.m[2][0] +
    m1.m[1][3] * m2.m[3][0];
    result.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] + m1.m[1][2] * m2.m[2][1] +
    m1.m[1][3] * m2.m[3][1];
    result.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] + m1.m[1][2] * m2.m[2][2] +
    m1.m[1][3] * m2.m[3][2];
    result.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] + m1.m[1][2] * m2.m[2][3] +
    m1.m[1][3] * m2.m[3][3];
    result.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] + m1.m[2][2] * m2.m[2][0] +
    m1.m[2][3] * m2.m[3][0];
    result.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] + m1.m[2][2] * m2.m[2][1] +
    m1.m[2][3] * m2.m[3][1];
    result.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] + m1.m[2][2] * m2.m[2][2] +
    m1.m[2][3] * m2.m[3][2];
    result.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] + m1.m[2][2] * m2.m[2][3] +
    m1.m[2][3] * m2.m[3][3];
    result.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] + m1.m[3][2] * m2.m[2][0] +
    m1.m[3][3] * m2.m[3][0];
    result.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] + m1.m[3][2] * m2.m[2][1] +
    m1.m[3][3] * m2.m[3][1];
    result.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] + m1.m[3][2] * m2.m[2][2] +
    m1.m[3][3] * m2.m[3][2];
    result.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] + m1.m[3][2] * m2.m[2][3] +
    m1.m[3][3] * m2.m[3][3];

    return result; 
}

Matrix4x4 MakeRotateMatrix(const Vector3& radian)
{
	Matrix4x4 result = { 0 };

	Matrix4x4 rotateX = MakeRoatateXMatix(radian.x);
	Matrix4x4 rotateY = MakeRoatateYMatix(radian.y);
	Matrix4x4 rotateZ = MakeRoatateZMatix(radian.z);

	result = Multiply(rotateX, Multiply(rotateY, rotateZ));

	return result;
}

//アフィン変換行列作成
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {

    Matrix4x4 result = MakeRotateMatrix(rotate);

    result.m[0][0] *= scale.x;
    result.m[0][1] *= scale.x;
    result.m[0][2] *= scale.x;

    result.m[1][0] *= scale.y;
    result.m[1][1] *= scale.y;
    result.m[1][2] *= scale.y;

    result.m[2][0] *= scale.z;
    result.m[2][1] *= scale.z;
    result.m[2][2] *= scale.z;

    result.m[3][0] = translate.x;
    result.m[3][1] = translate.y;
    result.m[3][2] = translate.z;

    return result;
}

float EaseInOut(float x1, float x2, float t)
{
    float easedT = -(std::cosf(std::numbers::pi_v<float> *t) - 1.0f) / 2.0f;
    return Lerp(x1, x2, easedT);
}

float Lerp(float x1, float x2, float t) {return (1.0f - t) * x1 + t * x2; }

Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t)
{
    return Vector3(Lerp(v1.x, v2.x, t),Lerp(v1.y, v2.y, t), Lerp(v1.z, v2.z,t));
}