#include "Matrix4.h"

/// <summary>
/// Default constructor that initialises the matrix to an identity matrix
/// </summary>
Matrix4::Matrix4()
	:mRows{Vector4(1, 0, 0, 0), Vector4(0, 1, 0, 0), Vector4(0, 0, 1, 0), Vector4(0, 0, 0, 1)}
{
}

/// <summary>
/// Constructor that takes 4 vectors as the 1st, 2nd, 3rd and 4th rows of the matrix
/// </summary>
/// <param name="pRow1">Row 1 of the matrix</param>
/// <param name="pRow2">Row 2 of the matrix</param>
/// <param name="pRow3">Row 3 of the matrix</param>
/// <param name="pRow4">Row 4 of the matrix</param>
Matrix4::Matrix4(const Vector4 & pRow1, const Vector4 & pRow2, const Vector4 & pRow3, const Vector4 & pRow4)
	:mRows{ pRow1, pRow2, pRow3, pRow4 }
{
}

/// <summary>
/// Constructor that takes 16 floats as the x, y, z and w components of each row of the matrix
/// </summary>
/// <param name="p11">X component of the first row of the matrix</param>
/// <param name="p12">Y component of the first row of the matrix</param>
/// <param name="p13">Z component of the first row of the matrix</param>
/// <param name="p14">W component of the first row of the matrix</param>
/// <param name="p21">X component of the second row of the matrix</param>
/// <param name="p22">Y component of the second row of the matrix</param>
/// <param name="p23">Z component of the second row of the matrix</param>
/// <param name="p24">W component of the second row of the matrix</param>
/// <param name="p31">X component of the third row of the matrix</param>
/// <param name="p32">Y component of the third row of the matrix</param>
/// <param name="p33">Z component of the third row of the matrix</param>
/// <param name="p34">W component of the third row of the matrix</param>
/// <param name="p41">X component of the fourth row of the matrix</param>
/// <param name="p42">Y component of the fourth row of the matrix</param>
/// <param name="p43">Z component of the fourth row of the matrix</param>
/// <param name="p44">W component of the fourth row of the matrix</param>
Matrix4::Matrix4(
	const float& p11, const float& p12, const float& p13, const float& p14,
	const float& p21, const float& p22, const float& p23, const float& p24,
	const float& p31, const float& p32, const float& p33, const float& p34,
	const float& p41, const float& p42, const float& p43, const float& p44)
	:mRows{ Vector4(p11, p12, p13, p14), Vector4(p21, p22, p23, p24), Vector4(p31, p32, p33, p34), Vector4(p41, p42, p43, p44) }
{
}

/// <summary>
/// Default destructor for Matrix4
/// </summary>
Matrix4::~Matrix4()
{
}

/// <summary>
/// Creates a rotation matrix around the y axis with a given angle in radians
/// </summary>
/// <param name="pAngle">Given angle of rotation</param>
/// <returns>Rotation matrix for a rotation around the x axis</returns>
Matrix4 Matrix4::RotationMatrixX(const float & pAngle)
{
	//Sin and cosin of angle
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
/// Creates a rotation matrix around the y axis with a given angle in radians
/// </summary>
/// <param name="pAngle">Given angle of rotation</param>
/// <returns>Rotation matrix for a rotation around the y axis</returns>
Matrix4 Matrix4::RotationMatrixY(const float & pAngle)
{
	//Sin and cosin of angle
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
/// Creates a rotation matrix around the z axis with a given angle in radians
/// </summary>
/// <param name="pAngle">Given angle of rotation</param>
/// <returns>Rotation matrix for a rotation around the z axis</returns>
Matrix4 Matrix4::RotationMatrixZ(const float & pAngle)
{
	//Sin and cosin of angle
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
/// Creates a rotation matrix around a given axis with a given angle in radians
/// </summary>
/// <param name="pAngle">Given angle of rotation</param>
/// <param name="pAxis">Given axis to rotation around</param>
/// <returns>Rotation matrix for a rotation around the given axis</returns>
Matrix4 Matrix4::RotationMatrixAxis(const float & pAngle, const Vector4 & pAxis)
{
	//Sin and cosin of angle
	const float s = sin(pAngle);
	const float c = cos(pAngle);
	const float oneSubC = 1 - c;

	//Squares of x, y and z components of axis
	const float xSqrd = pAxis.X() * pAxis.X();
	const float ySqrd = pAxis.Y() * pAxis.Y();
	const float zSqrd = pAxis.Z() * pAxis.Z();

	//X, y and z components multiplied by sin
	const float xS = pAxis.X() * s;
	const float yS = pAxis.Y() * s;
	const float zS = pAxis.Z() * s;

	//X, y and z components multiplied by each other component
	const float xY = pAxis.X() * pAxis.Y();
	const float xZ = pAxis.X() * pAxis.Z();
	const float yZ = pAxis.Y() * pAxis.Z();

	Matrix4 matrix(
		//Column 1             // Column 2            //Column 3             //Column 4
		(c + xSqrd) * oneSubC, (xY * oneSubC) - zS,   (xZ * oneSubC) + yS,   0,  //Row 1
		(xY * oneSubC) + zS,   (c + ySqrd) * oneSubC, (yZ * oneSubC) - xS,   0,  //Row 2
		(xZ * oneSubC) - yS,   (yZ * oneSubC) + xS,   (c + zSqrd) * oneSubC, 0,  //Row 3
		0,                     0,                     0,                     1); //Row 4

	return matrix;
}

/// <summary>
/// Creates a translation matrix from a given vector
/// </summary>
/// <param name="pVector">Given vector containing x, y, z components of translation</param>
/// <returns>Translation matrix containing the given translation vector</returns>
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
/// Calculates the transpose of a given matrix
/// </summary>
/// <param name="pMatrix">Given matrix to transpose</param>
/// <returns>Transposed matrix of the given matrix</returns>
Matrix4 Matrix4::Transpose(const Matrix4 & pMatrix)
{
	Matrix4 matrix(
		pMatrix.m11, pMatrix.m21, pMatrix.m31, pMatrix.m41,
		pMatrix.m12, pMatrix.m22, pMatrix.m32, pMatrix.m42,
		pMatrix.m13, pMatrix.m23, pMatrix.m33, pMatrix.m43,
		pMatrix.m14, pMatrix.m24, pMatrix.m34, pMatrix.m44);

	return matrix;
}

/// <summary>
/// Multiplies this matrix with a given matrix
/// </summary>
/// <param name="rhs">Given matrix to multiply by</param>
/// <returns>Result of the multiplication</returns>
Matrix4 & Matrix4::operator*=(const Matrix4 & rhs)
{
	//Calculates dot product of the 1st row with each column of the given matrix to get the new values for the 1st row of the matrix
	m11 = mRows[0].Dot(Vector4(rhs._11(), rhs._21(), rhs._31(), rhs._41()));
	m12 = mRows[0].Dot(Vector4(rhs._12(), rhs._22(), rhs._32(), rhs._42()));
	m13 = mRows[0].Dot(Vector4(rhs._13(), rhs._23(), rhs._33(), rhs._43()));
	m14 = mRows[0].Dot(Vector4(rhs._14(), rhs._24(), rhs._34(), rhs._44()));

	//Calculates dot product of the 2nd row with each column of the given matrix to get the new values for the 2nd row of the matrix
	m21 = mRows[1].Dot(Vector4(rhs._11(), rhs._21(), rhs._31(), rhs._41()));
	m22 = mRows[1].Dot(Vector4(rhs._12(), rhs._22(), rhs._32(), rhs._42()));
	m23 = mRows[1].Dot(Vector4(rhs._13(), rhs._23(), rhs._33(), rhs._43()));
	m24 = mRows[1].Dot(Vector4(rhs._14(), rhs._24(), rhs._34(), rhs._44()));

	//Calculates dot product of the 3rd row with each column of the given matrix to get the new values for the 3rd row of the matrix
	m31 = mRows[2].Dot(Vector4(rhs._11(), rhs._21(), rhs._31(), rhs._41()));
	m32 = mRows[2].Dot(Vector4(rhs._12(), rhs._22(), rhs._32(), rhs._42()));
	m33 = mRows[2].Dot(Vector4(rhs._13(), rhs._23(), rhs._33(), rhs._43()));
	m34 = mRows[2].Dot(Vector4(rhs._14(), rhs._24(), rhs._34(), rhs._44()));

	//Calculates dot product of the 4th row with each column of the given matrix to get the new values for the 4th row of the matrix
	m41 = mRows[3].Dot(Vector4(rhs._11(), rhs._21(), rhs._31(), rhs._41()));
	m42 = mRows[3].Dot(Vector4(rhs._12(), rhs._22(), rhs._32(), rhs._42()));
	m43 = mRows[3].Dot(Vector4(rhs._13(), rhs._23(), rhs._33(), rhs._43()));
	m44 = mRows[3].Dot(Vector4(rhs._14(), rhs._24(), rhs._34(), rhs._44()));

	return *this;
}

/// <summary>
/// Accessor for the value in the first row and first column of the matrix
/// </summary>
/// <returns>Value at 11 in the matrix</returns>
const float & Matrix4::_11() const
{
	return m11;
}

/// <summary>
/// Accessor for the value in the first row and second column of the matrix
/// </summary>
/// <returns>Value at 12 in the matrix</returns>
const float & Matrix4::_12() const
{
	return m12;
}

/// <summary>
/// Accessor for the value in the first row and third column of the matrix
/// </summary>
/// <returns>Value at 13 in the matrix</returns>
const float & Matrix4::_13() const
{
	return m13;
}

/// <summary>
/// Accessor for the value in the first row and fourth column of the matrix
/// </summary>
/// <returns>Value at 14 in the matrix</returns>
const float & Matrix4::_14() const
{
	return m14;
}

/// <summary>
/// Accessor for the value in the second row and first column of the matrix
/// </summary>
/// <returns>Value at 21 in the matrix</returns>
const float & Matrix4::_21() const
{
	return m21;
}

/// <summary>
/// Accessor for the value in the second row and second column of the matrix
/// </summary>
/// <returns>Value at 22 in the matrix</returns>
const float & Matrix4::_22() const
{
	return m22;
}

/// <summary>
/// Accessor for the value in the second row and third column of the matrix
/// </summary>
/// <returns>Value at 23 in the matrix</returns>
const float & Matrix4::_23() const
{
	return m23;
}

/// <summary>
/// Accessor for the value in the second row and fourth column of the matrix
/// </summary>
/// <returns>Value at 24 in the matrix</returns>
const float & Matrix4::_24() const
{
	return m24;
}

/// <summary>
/// Accessor for the value in the third row and first column of the matrix
/// </summary>
/// <returns>Value at 31 in the matrix</returns>
const float & Matrix4::_31() const
{
	return m31;
}

/// <summary>
/// Accessor for the value in the third row and second column of the matrix
/// </summary>
/// <returns>Value at 32 in the matrix</returns>
const float & Matrix4::_32() const
{
	return m32;
}

/// <summary>
/// Accessor for the value in the third row and third column of the matrix
/// </summary>
/// <returns>Value at 33 in the matrix</returns>
const float & Matrix4::_33() const
{
	return m33;
}

/// <summary>
/// Accessor for the value in the third row and fourth column of the matrix
/// </summary>
/// <returns>Value at 34 in the matrix</returns>
const float & Matrix4::_34() const
{
	return m34;
}

/// <summary>
/// Accessor for the value in the fourth row and first column of the matrix
/// </summary>
/// <returns>Value at 41 in the matrix</returns>
const float & Matrix4::_41() const
{
	return m41;
}

/// <summary>
/// Accessor for the value in the fourth row and second column of the matrix
/// </summary>
/// <returns>Value at 42 in the matrix</returns>
const float & Matrix4::_42() const
{
	return m42;
}

/// <summary>
/// Accessor for the value in the fourth row and third column of the matrix
/// </summary>
/// <returns>Value at 43 in the matrix</returns>
const float & Matrix4::_43() const
{
	return m43;
}

/// <summary>
/// Accessor for the value in the fourth row and fourth column of the matrix
/// </summary>
/// <returns>Value at 44 in the matrix</returns>
const float & Matrix4::_44() const
{
	return m44;
}

