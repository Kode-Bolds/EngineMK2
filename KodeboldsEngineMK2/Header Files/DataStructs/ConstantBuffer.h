#pragma once
#include <DirectXMath.h>

struct ConstantBuffer
{
	DirectX::XMFLOAT4X4 mWorld;
	DirectX::XMFLOAT4X4 mView;
	DirectX::XMFLOAT4X4 mProj;
	DirectX::XMFLOAT4 mLightColour;
	DirectX::XMFLOAT4 mLightPosition;
	DirectX::XMFLOAT4 mCameraPosition;
	DirectX::XMFLOAT4 mColour;
};
