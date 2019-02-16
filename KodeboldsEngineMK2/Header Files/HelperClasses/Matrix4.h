#pragma once
#include <cmath>
#include "Vector4.h"

class Matrix4
{
private:
	Vector4 mRow1;
	Vector4 mRow2;
	Vector4 mRow3;
	Vector4 mRow4;

public:
	//Structors
	Matrix4();
	~Matrix4();

	//Accessors
	const Vector4& Row1() const;
	const Vector4& Row2() const;
	const Vector4& Row3() const;
	const Vector4& Row4() const;

	//Static methods for constructing rotation, translation and scale matricies from vectors
	static Matrix4 RotationMatrix(const Vector4& pVector);
	static Matrix4 TranslationMatrix(const Vector4& pVector);
	static Matrix4 ScaleMatrix(const Vector4& pVector);

	//Operator overloads
	Matrix4& operator*=(const Matrix4& rhs);
};

//Operator overloads
inline Matrix4 operator*(Matrix4 lhs, const Matrix4& rhs) { lhs *= rhs; return lhs; }