#pragma once
#include <cmath>

class Vector4
{
private:
	float mX;
	float mY;
	float mZ;
	float mW;

public:
	//Structors
	Vector4();
	Vector4(const float x, const float y, const float z, const float w);
	~Vector4();

	//Accessors
	float& X();
	const float& X() const;
	float& Y();
	const float& Y() const;
	float& Z();
	const float& Z() const;
	float& W();
	const float& W() const;

	//Maths methods
	float Magnitude() const;
	float Dot(const Vector4& b) const;
	Vector4& Clamp(float pMagnitude);
	Vector4& Normalise();

	//Operator overloads
	Vector4& operator+=(const Vector4& rhs);
	Vector4& operator-=(const Vector4& rhs);
	Vector4& operator*=(const float& rhs);
};

//Operator overloads
inline Vector4 operator+(Vector4 lhs, const Vector4& rhs) { lhs += rhs; return lhs; }
inline Vector4 operator-(Vector4 lhs, const Vector4& rhs) {	lhs -= rhs;	return lhs; }
inline Vector4 operator*(Vector4 lhs, const float& rhs) { lhs *= rhs;	return lhs; }
