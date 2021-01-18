#include "..\..\Header\Math\Vector4.h"

GatesEngine::Vector4::Vector4()
	:x(0), y(0), z(0), w(0)
{
}

GatesEngine::Vector4::Vector4(float x, float y, float z, float w)
	: x(x), y(y), z(z), w(w)
{
}

GatesEngine::Vector4 GatesEngine::Vector4::operator+()
{
	return *this;
}

GatesEngine::Vector4 GatesEngine::Vector4::operator-()
{
	return Vector4(-x, -y, -z, -w);
}

GatesEngine::Vector4 & GatesEngine::Vector4::operator+=(const Vector4 & v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

GatesEngine::Vector4 & GatesEngine::Vector4::operator-=(const Vector4 & v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

GatesEngine::Vector4 & GatesEngine::Vector4::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	w *= s;
	return *this;
}

GatesEngine::Vector4 & GatesEngine::Vector4::operator/=(float s)
{
	x /= s;
	y /= s;
	z /= s;
	w /= s;
	return *this;
}

const GatesEngine::Vector4 GatesEngine::operator+(const Vector4 & v1, const Vector4 & v2)
{
	Vector4 a(v1);
	return a += v2;
}

const GatesEngine::Vector4 GatesEngine::operator-(const Vector4 & v1, const Vector4 & v2)
{
	Vector4 a(v1);
	return a -= v2;
}

const GatesEngine::Vector4 GatesEngine::operator*(const Vector4& v, float s)
{
	Vector4 a(v);
	return a *= s;
}

const GatesEngine::Vector4 GatesEngine::operator*(float s, const Vector4& v)
{
	return v * s;
}

const GatesEngine::Vector4 GatesEngine::operator/(const Vector4& v, float s)
{
	Vector4 a(v);
	return a /= s;
}

const GatesEngine::Vector4 GatesEngine::operator/(float s, const Vector4& v)
{
	return v / s;
}
