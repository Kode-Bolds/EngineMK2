#include "Matrix4.h"

Matrix4::Matrix4()
	:mRow1(1, 0, 0 ,0), mRow2(0, 1, 0, 0), mRow3(0, 0, 1, 0), mRow4(0, 0, 0, 1)
{
}

Matrix4::~Matrix4()
{
}

const Vector4 & Matrix4::Row1() const
{
	return mRow1;
}

const Vector4 & Matrix4::Row2() const
{
	return mRow2;
}

const Vector4 & Matrix4::Row3() const
{
	return mRow3;
}

const Vector4 & Matrix4::Row4() const
{
	return mRow4;
}

Matrix4 Matrix4::RotationMatrix(const Vector4 & pVector)
{
	Matrix4 matrix;
	
	return matrix;
}

Matrix4 Matrix4::TranslationMatrix(const Vector4 & pVector)
{
	Matrix4 matrix;
	matrix.mRow1.W() = pVector.X();
	matrix.mRow2.W() = pVector.Y();
	matrix.mRow3.W() = pVector.Z();
	return matrix;
}

Matrix4 Matrix4::ScaleMatrix(const Vector4 & pVector)
{
	return Matrix4();
}

Matrix4 & Matrix4::operator*=(const Matrix4 & rhs)
{
	return *this;
}
