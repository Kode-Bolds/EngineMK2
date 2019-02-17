#include "Matrix4.h"

/// <summary>
/// 
/// </summary>
Matrix4::Matrix4()
	:mRows{Vector4(1, 0, 0, 0), Vector4(0, 1, 0, 0), Vector4(0, 0, 1, 0), Vector4(0, 0, 0, 1)}
{
}

/// <summary>
/// 
/// </summary>
/// <param name="pRow1"></param>
/// <param name="pRow2"></param>
/// <param name="pRow3"></param>
/// <param name="pRow4"></param>
Matrix4::Matrix4(const Vector4 & pRow1, const Vector4 & pRow2, const Vector4 & pRow3, const Vector4 & pRow4)
	:mRows{ pRow1, pRow2, pRow3, pRow4 }
{
}

/// <summary>
/// 
/// </summary>
/// <param name="p11"></param>
/// <param name="p12"></param>
/// <param name="p13"></param>
/// <param name="p14"></param>
/// <param name="p21"></param>
/// <param name="p22"></param>
/// <param name="p23"></param>
/// <param name="p24"></param>
/// <param name="p31"></param>
/// <param name="p32"></param>
/// <param name="p33"></param>
/// <param name="p34"></param>
/// <param name="p41"></param>
/// <param name="p42"></param>
/// <param name="p43"></param>
/// <param name="p44"></param>
Matrix4::Matrix4(
	const float& p11, const float& p12, const float& p13, const float& p14,
	const float& p21, const float& p22, const float& p23, const float& p24,
	const float& p31, const float& p32, const float& p33, const float& p34,
	const float& p41, const float& p42, const float& p43, const float& p44)
	:mRows{ Vector4(p11, p12, p13, p14), Vector4(p21, p22, p23, p24), Vector4(p31, p32, p33, p34), Vector4(p41, p42, p43, p44) }
{
}

/// <summary>
/// 
/// </summary>
Matrix4::~Matrix4()
{
}

/// <summary>
/// 
/// </summary>
/// <param name="pAngle"></param>
/// <returns></returns>
Matrix4 Matrix4::RotationMatrixX(const float & pAngle)
{
	float s = sin(pAngle);
	float c = cos(pAngle);

	Matrix4 matrix(
		1, 0, 0, 0,
		0, c,-s, 0,
		0, s, c, 0,
		0, 0, 0, 1);

	return matrix;
}

/// <summary>
/// 
/// </summary>
/// <param name="pAngle"></param>
/// <returns></returns>
Matrix4 Matrix4::RotationMatrixY(const float & pAngle)
{
	float s = sin(pAngle);
	float c = cos(pAngle);

	Matrix4 matrix(
		c, 0, s, 0,
		0, 1, 0, 0,
	   -s, 0, c, 0,
		0, 0, 0, 1);

	return matrix;
}

/// <summary>
/// 
/// </summary>
/// <param name="pAngle"></param>
/// <returns></returns>
Matrix4 Matrix4::RotationMatrixZ(const float & pAngle)
{
	float s = sin(pAngle);
	float c = cos(pAngle);

	Matrix4 matrix(
		c,-s, 0, 0,
		s, c, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);

	return matrix;
}

/// <summary>
/// 
/// </summary>
/// <param name="pVector"></param>
/// <returns></returns>
Matrix4 Matrix4::TranslationMatrix(const Vector4 & pVector)
{
	Matrix4 matrix(
		1, 0, 0, pVector.X(),
		0, 1, 0, pVector.Y(),
		0, 0, 1, pVector.Z(),
		0, 0, 0, 1);
	return matrix;
}

/// <summary>
/// 
/// </summary>
/// <param name="pVector"></param>
/// <returns></returns>
Matrix4 Matrix4::ScaleMatrix(const Vector4 & pVector)
{
	Matrix4 matrix(
		pVector.X(), 0,			  0,		   0,
		0,			 pVector.Y(), 0,		   0,
		0,			 0,			  pVector.Z(), 0,
		0,			 0,			  0,		   1);
	return matrix;
}

/// <summary>
/// 
/// </summary>
/// <param name="rhs"></param>
/// <returns></returns>
Matrix4 & Matrix4::operator*=(const Matrix4 & rhs)
{
	return *this;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
const float & Matrix4::_11() const
{
	return m11;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
const float & Matrix4::_12() const
{
	return m12;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
const float & Matrix4::_13() const
{
	return m13;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
const float & Matrix4::_14() const
{
	return m14;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
const float & Matrix4::_21() const
{
	return m21;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
const float & Matrix4::_22() const
{
	return m22;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
const float & Matrix4::_23() const
{
	return m23;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
const float & Matrix4::_24() const
{
	return m24;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
const float & Matrix4::_33() const
{
	return m31;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
const float & Matrix4::_32() const
{
	return m32;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
const float & Matrix4::_31() const
{
	return m33;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
const float & Matrix4::_34() const
{
	return m34;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
const float & Matrix4::_43() const
{
	return m41;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
const float & Matrix4::_42() const
{
	return m42;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
const float & Matrix4::_41() const
{
	return m43;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
const float & Matrix4::_44() const
{
	return m44;
}
