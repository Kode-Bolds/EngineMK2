#include "Vector3.h"

/// <summary>
/// 
/// </summary>
Vector3::Vector3()
	:mX(0), mY(0), mZ(0)
{
}

/// <summary>
/// 
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="z"></param>
Vector3::Vector3(const float x, const float y, const float z)
	:mX(x), mY(y), mZ(z)
{
}

/// <summary>
/// 
/// </summary>
Vector3::~Vector3()
{
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
float & Vector3::X()
{
	return mX;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
float & Vector3::Y()
{
	return mY;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
float & Vector3::Z()
{
	return mZ;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
float Vector3::Magnitude() const
{
	return sqrt((mX * mX) + (mY * mY) + (mZ * mZ));
}

/// <summary>
/// 
/// </summary>
/// <param name="b"></param>
/// <returns></returns>
float Vector3::Dot(const Vector3 & b) const
{
	return (mX * b.mX) + (mY * b.mY) + (mZ * b.mZ);
}

/// <summary>
/// 
/// </summary>
/// <param name="pMagnitude"></param>
/// <returns></returns>
Vector3 & Vector3::Clamp(float pMagnitude)
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
Vector3 & Vector3::Normalise()
{
	return this->Clamp(1);
}

/// <summary>
/// 
/// </summary>
/// <param name="rhs"></param>
/// <returns></returns>
Vector3 & Vector3::operator+=(const Vector3 & rhs)
{
	mX += rhs.mX;
	mY += rhs.mY;
	mZ += rhs.mZ;
	return *this;
}

/// <summary>
/// 
/// </summary>
/// <param name="rhs"></param>
/// <returns></returns>
Vector3 & Vector3::operator-=(const Vector3 & rhs)
{
	mX -= rhs.mX;
	mY -= rhs.mY;
	mZ -= rhs.mZ;
	return *this;
}

/// <summary>
/// 
/// </summary>
/// <param name="rhs"></param>
/// <returns></returns>
Vector3 & Vector3::operator*=(const float& rhs)
{
	mX *= rhs;
	mY *= rhs;
	mZ *= rhs;
	return *this;
}
