#pragma once
#include <DirectXMath.h>
#include "Vector4.h"

struct Velocity
{
	Vector4 mVelocity;
	Vector4 mAcceleration;
	float maxSpeed;
};
