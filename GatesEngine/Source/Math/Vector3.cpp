#include "..\..\Header\Math\Vector3.h"
#include <math.h>
GatesEngine::Vector3::Vector3() :x(0), y(0), z(0)
{
}

GatesEngine::Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
{
}

float GatesEngine::Vector3::Length()
{
	return sqrtf(x * x + y * y + z * z);
}

GatesEngine::Vector3 GatesEngine::Vector3::Normalize()
{
	return *this / Length();
}

float GatesEngine::Vector3::Distance(const Vector3 & v1, const Vector3 & v2)
{
	Vector3 v = v1 - v2;
	return v.Length();;
}

GatesEngine::Vector3 GatesEngine::Vector3::Normalize(const Vector3 & v)
{
	Vector3 v1 = v;
	return v1 / v1.Length();
}

GatesEngine::Vector3 GatesEngine::Vector3::Cross(const Vector3 & v1, const Vector3 & v2)
{
	Vector3 v = Vector3(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
	return v;
}

float GatesEngine::Vector3::Dot(const Vector3 & v1, const Vector3 & v2)
{
	float value = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return value;
}

GatesEngine::Vector3 GatesEngine::Vector3::Lerp(const Vector3 & s, const Vector3 & e, float t)
{
	return s * (1.0f - t) + e * t;
}

GatesEngine::Vector3 GatesEngine::Vector3::operator+()
{
	return *this;
}

GatesEngine::Vector3 GatesEngine::Vector3::operator-()
{
	return Vector3(-x, -y, -z);
}

GatesEngine::Vector3 & GatesEngine::Vector3::operator+=(const Vector3 & v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

GatesEngine::Vector3 & GatesEngine::Vector3::operator-=(const Vector3 & v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

GatesEngine::Vector3 & GatesEngine::Vector3::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

GatesEngine::Vector3 & GatesEngine::Vector3::operator/=(float s)
{
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

const GatesEngine::Vector3 GatesEngine::operator+(const Vector3 & v1, const Vector3 & v2)
{
	Vector3 a(v1);
	return a += v2;
}

const GatesEngine::Vector3 GatesEngine::operator-(const Vector3 & v1, const Vector3 & v2)
{
	Vector3 a(v1);
	return a -= v2;
}

const GatesEngine::Vector3 GatesEngine::operator*(const Vector3& v, float s)
{
	Vector3 a(v);
	return a *= s;
}

const GatesEngine::Vector3 GatesEngine::operator*(float s, const Vector3& v)
{
	return v * s;
}

const GatesEngine::Vector3 GatesEngine::operator/(const Vector3& v, float s)
{
	Vector3 a(v);
	return a /= s;
}

const GatesEngine::Vector3 GatesEngine::operator/(float s, const Vector3& v)
{

	return v / s;
}