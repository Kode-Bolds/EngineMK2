#pragma once
#include <DirectXMath.h>

struct Transform
{
	DirectX::XMFLOAT4X4 mTransform;
	DirectX::XMFLOAT3 mTranslation;
	DirectX::XMFLOAT3 mRotation;
	DirectX::XMFLOAT3 mScale;
	DirectX::XMFLOAT3 mForward;
	DirectX::XMFLOAT3 mRight;
	DirectX::XMFLOAT3 mUp;
};