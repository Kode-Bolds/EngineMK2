#include "Vector3.h"

/// <summary>
/// 
/// </summary>
/// <returns></returns>
float & Vector3::X()
{
	return x;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
float & Vector3::Y()
{
	return y;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
float & Vector3::Z()
{
	return z;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
float Vector3::Magnitude() const
{
	return sqrt((x * x) + (y * y) + (z * z));
}

/// <summary>
/// 
/// </summary>
/// <param name="b"></param>
/// <returns></returns>
float Vector3::Dot(const Vector3 & b) const
{
	return (x * b.x) + (y * b.y) + (z * b.z);
}

/// <summary>
/// 
/// </summary>
/// <param name="rhs"></param>
/// <returns></returns>
Vector3 & Vector3::operator+=(const Vector3 & rhs)
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

/// <summary>
/// 
/// </summary>
/// <param name="rhs"></param>
/// <returns></returns>
Vector3 & Vector3::operator-=(const Vector3 & rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}
