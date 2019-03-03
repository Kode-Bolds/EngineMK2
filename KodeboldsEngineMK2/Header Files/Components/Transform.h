#pragma once
#include <DirectXMath.h>
#include "Vector4.h"
#include "Matrix4.h"

struct Transform
{
	Matrix4 mTransform;
	Vector4 mTranslation;
	Vector4 mRotation;
	Vector4 mScale;
	Vector4 mForward;
	Vector4 mRight;
	Vector4 mUp;
};