#pragma once
#include <cmath>

class Vector3
{
private:
	float x;
	float y;
	float z;

public:
	float& X();
	float& Y();
	float& Z();
	float Magnitude() const;
	float Dot(const Vector3& b) const;

	//TODO: test returning a reference to this doesnt cause bugs
	Vector3& Multiply(float pScalar);
	Vector3& Clamp(float pMagnitude);
	Vector3& Normalise();

	Vector3& operator+=(const Vector3& rhs);
	Vector3& operator-=(const Vector3& rhs);
	Vector3& operator*=(const float& rhs);
};

//+/- operators implemented using the += and -= operators
Vector3 operator+(Vector3 lhs, const Vector3& rhs){ lhs += rhs; return lhs; }
Vector3 operator-(Vector3 lhs, const Vector3& rhs){	lhs -= rhs;	return lhs; }
Vector3 operator*(Vector3 lhs, const float& rhs) { lhs *= rhs;	return lhs; }
