#pragma once
#include <DirectXMath.h>
#include "Vector3.h"

struct Transform
{
	DirectX::XMFLOAT4X4 mTransform;
	Vector3 mTranslation;
	Vector3 mRotation;
	Vector3 mScale;
	Vector3 mForward;
	Vector3 mRight;
	Vector3 mUp;
};