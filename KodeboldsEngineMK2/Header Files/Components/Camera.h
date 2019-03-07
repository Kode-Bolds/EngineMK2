#pragma once
#include "Vector4.h"

struct Camera
{
	KodeBoldsMath::Vector4 mLookAt;
	KodeBoldsMath::Vector4 mUp;
	KodeBoldsMath::Vector4 mRight;

	float mFOV;
	float mNear;
	float mFar;
};