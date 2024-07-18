#include "MathUtilityForText.h"
Vector3& operator+=(Vector3& lhv, const Vector3& rhv)
{
    lhv.x += rhv.x;
    lhv.y += rhv.y;
    lhv.z += rhv.z;
    return lhv;
}

Vector3& operator*=(Vector3& lhv, const Vector3& rhv)
{
    lhv.x *= rhv.x;
    lhv.y *= rhv.y;
    lhv.z *= rhv.z;
    return lhv;
}

Vector3& operator+(Vector3 a,const Vector3 b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

Vector3 sumVector(Vector3 a, Vector3 b)
{
    Vector3 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return result;
}

Vector3 MultiplyVectorFloat(Vector3 a, float b)
{
    Vector3 result;
    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;
    return result;
}
