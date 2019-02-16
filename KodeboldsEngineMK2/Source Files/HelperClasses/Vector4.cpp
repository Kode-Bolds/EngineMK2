#include "Vector4.h"

/// <summary>
/// 
/// </summary>
Vector4::Vector4()
	:mX(0), mY(0), mZ(0), mW(0)
{
}

/// <summary>
/// 
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
Vector4::Vector4(const float x, const float y, const float z, const float w)
	:mX(x), mY(y), mZ(z), mW(w)
{
}

/// <summary>
/// 
/// </summary>
Vector4::~Vector4()
{
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
float & Vector4::X()
{
	return mX;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
const float & Vector4::X() const
{
	return mX;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
float & Vector4::Y()
{
	return mY;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
const float & Vector4::Y() const
{
	return mY;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
float & Vector4::Z()
{
	return mZ;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
const float & Vector4::Z() const
{
	return mZ;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
float & Vector4::W()
{
	return mW;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
const float & Vector4::W() const
{
	return mW;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
float Vector4::Magnitude() const
{
	return sqrt((mX * mX) + (mY * mY) + (mZ * mZ));
}

/// <summary>
/// 
/// </summary>
/// <param name="b"></param>
/// <returns></returns>
float Vector4::Dot(const Vector4 & b) const
{
	return (mX * b.mX) + (mY * b.mY) + (mZ * b.mZ);
}

/// <summary>
/// 
/// </summary>
/// <param name="pMagnitude"></param>
/// <returns></returns>
Vector4 & Vector4::Clamp(float pMagnitude)
{
	float magnitude = this->Magnitude();
	if (magnitude > pMagnitude)
	{
		float scale = pMagnitude / magnitude;
		return *this *= scale;
	}
	return *this;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
Vector4 & Vector4::Normalise()
{
	return this->Clamp(1);
}

/// <summary>
/// 
/// </summary>
/// <param name="rhs"></param>
/// <returns></returns>
Vector4 & Vector4::operator+=(const Vector4 & rhs)
{
	mX += rhs.mX;
	mY += rhs.mY;
	mZ += rhs.mZ;
	mW += rhs.mW;
	return *this;
}

/// <summary>
/// 
/// </summary>
/// <param name="rhs"></param>
/// <returns></returns>
Vector4 & Vector4::operator-=(const Vector4 & rhs)
{
	mX -= rhs.mX;
	mY -= rhs.mY;
	mZ -= rhs.mZ;
	mW -= rhs.mW;
	return *this;
}

/// <summary>
/// 
/// </summary>
/// <param name="rhs"></param>
/// <returns></returns>
Vector4 & Vector4::operator*=(const float& rhs)
{
	mX *= rhs;
	mY *= rhs;
	mZ *= rhs;
	mW *= rhs;
	return *this;
}
