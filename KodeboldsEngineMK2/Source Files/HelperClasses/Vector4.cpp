#include "Vector4.h"

/// <summary>
/// Default constructor for Vector4, initialises all values to 0
/// </summary>
Vector4::Vector4()
	:mX(0), mY(0), mZ(0), mW(0)
{
}

/// <summary>
/// Constructor that takes 4 floats for the x, y, z and w components of the vector
/// </summary>
/// <param name="x">x component of the vector</param>
/// <param name="y">y component of the vector</param>
/// <param name="z">z component of the vector</param>
/// <param name="w">w component of the vector</param>
Vector4::Vector4(const float x, const float y, const float z, const float w)
	:mX(x), mY(y), mZ(z), mW(w)
{
}

/// <summary>
/// Default destructor for Vector4
/// </summary>
Vector4::~Vector4()
{
}

/// <summary>
/// Non-const accessor for the X component of the vector
/// </summary>
/// <returns>X component of the vector</returns>
float & Vector4::X()
{
	return mX;
}

/// <summary>
/// Const accessor for the X component of the vector
/// </summary>
/// <returns>X component of the vector</returns>
const float & Vector4::X() const
{
	return mX;
}

/// <summary>
/// Non-const accessor for the Y component of the vector
/// </summary>
/// <returns>Y component of the vector</returns>
float & Vector4::Y()
{
	return mY;
}

/// <summary>
/// Const accessor for the Y component of the vector
/// </summary>
/// <returns>Y component of the vector</returns>
const float & Vector4::Y() const
{
	return mY;
}

/// <summary>
/// Non-const accessor for the Z component of the vector
/// </summary>
/// <returns>Z component of the vector</returns>
float & Vector4::Z()
{
	return mZ;
}

/// <summary>
/// Const accessor for the Z component of the vector
/// </summary>
/// <returns>Z component of the vector</returns>
const float & Vector4::Z() const
{
	return mZ;
}

/// <summary>
/// Non-const accessor for the W component of the vector
/// </summary>
/// <returns>W component of the vector</returns>
float & Vector4::W()
{
	return mW;
}

/// <summary>
/// Const accessor for the W component of the vector
/// </summary>
/// <returns>W component of the vector</returns>
const float & Vector4::W() const
{
	return mW;
}

/// <summary>
/// Calculates and returns the magnitude of the vector
/// </summary>
/// <returns>Magnitude of the vector</returns>
float Vector4::Magnitude() const
{
	return sqrt((mX * mX) + (mY * mY) + (mZ * mZ));
}

/// <summary>
/// Calculates and returns the dot product between this vector and a given vector
/// </summary>
/// <param name="b">Given vector to do this vector with</param>
/// <returns>Dot product of the two vectors</returns>
float Vector4::Dot(const Vector4 & b) const
{
	return (mX * b.mX) + (mY * b.mY) + (mZ * b.mZ);
}

/// <summary>
/// Clamps this vector magnitude to a given value
/// </summary>
/// <param name="pMagnitude">Given magnitude to clamp to</param>
/// <returns>Clamped vector</returns>
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
/// Normalises this vector
/// </summary>
/// <returns>Normalised vector</returns>
Vector4 & Vector4::Normalise()
{
	return this->Clamp(1);
}

/// <summary>
/// += operator for addition of two vector4s
/// </summary>
/// <param name="rhs">Vector to add to this vector</param>
/// <returns>Sum of the two vectors</returns>
Vector4 & Vector4::operator+=(const Vector4 & rhs)
{
	mX += rhs.mX;
	mY += rhs.mY;
	mZ += rhs.mZ;
	mW += rhs.mW;
	return *this;
}

/// <summary>
/// -= operator for the subtraction of two vector4s
/// </summary>
/// <param name="rhs">Vector to subtract from this vector</param>
/// <returns>Difference between the vectors</returns>
Vector4 & Vector4::operator-=(const Vector4 & rhs)
{
	mX -= rhs.mX;
	mY -= rhs.mY;
	mZ -= rhs.mZ;
	mW -= rhs.mW;
	return *this;
}

/// <summary>
/// *= operator for the multiplication of two vector4s
/// </summary>
/// <param name="rhs">Vector to multiply this vector by</param>
/// <returns>Result of the multiplication</returns>
Vector4 & Vector4::operator*=(const float& rhs)
{
	mX *= rhs;
	mY *= rhs;
	mZ *= rhs;
	mW *= rhs;
	return *this;
}
