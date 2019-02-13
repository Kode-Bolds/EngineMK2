#pragma once
#include <DirectXMath.h>
#include "Vector3.h"

struct Velocity
{
	Vector3 mVelocity;
	Vector3 mAcceleration;
	float maxSpeed;
};
