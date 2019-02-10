#pragma once
#include <DirectXMath.h>

struct Velocity
{
	DirectX::XMFLOAT3 mVelocity;
	DirectX::XMFLOAT3 mAcceleration;
	float maxSpeed;
};
