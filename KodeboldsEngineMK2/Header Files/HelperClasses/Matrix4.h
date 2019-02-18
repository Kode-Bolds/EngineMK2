#pragma once
#include <cmath>
#include "Vector4.h"

class Matrix4
{
private:
	union 
	{
		Vector4 mRows[4];
		struct
		{
			//Column 1 //Column 2 //Column 3 //Column 4
			float m11; float m12; float m13; float m14; //Row 1
			float m21; float m22; float m23; float m24; //Row 2
			float m31; float m32; float m33; float m34; //Row 3
			float m41; float m42; float m43; float m44; //Row 4
		};
	};

public:
	//Structors
	Matrix4();
	Matrix4(const Vector4& pRow1, const Vector4& pRow2, const Vector4& pRow3, const Vector4& pRow4);
	Matrix4(
		const float& p11, const float& p12, const float& p13, const float& p14,
		const float& p21, const float& p22, const float& p23, const float& p24,
		const float& p31, const float& p32, const float& p33, const float& p34,
		const float& p41, const float& p42, const float& p43, const float& p44);
	~Matrix4();

	//Accessors
	//Column 1				  //Column 2                //Column 3                //Column 4
	const float& _11() const; const float& _12() const; const float& _13() const; const float& _14() const; //Row 1
	const float& _21() const; const float& _22() const; const float& _23() const; const float& _24() const; //Row 2
	const float& _31() const; const float& _32() const; const float& _33() const; const float& _34() const; //Row 3
	const float& _41() const; const float& _42() const; const float& _43() const; const float& _44() const; //Row 4

	//Static methods for constructing rotation, translation and scale matricies
	static Matrix4 RotationMatrixX(const float& pAngle);
	static Matrix4 RotationMatrixY(const float& pAngle);
	static Matrix4 RotationMatrixZ(const float& pAngle);
	static Matrix4 RotationMatrixAxis(const float& pAngle, const Vector4& pAxis);
	static Matrix4 TranslationMatrix(const Vector4& pVector);
	static Matrix4 ScaleMatrix(const Vector4& pVector);
	static Matrix4 Transpose(const Matrix4& pMatrix);

	//Operator overloads
	Matrix4& operator*=(const Matrix4& rhs);
};

//Operator overloads
inline Matrix4 operator*(Matrix4 lhs, const Matrix4& rhs) { lhs *= rhs; return lhs; }