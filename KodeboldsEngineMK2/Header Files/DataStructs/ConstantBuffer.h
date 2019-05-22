#pragma once
#include <DirectXMath.h>

struct ConstantBuffer
{
	DirectX::XMFLOAT4X4 mWorld;
	DirectX::XMFLOAT4X4 mView;
	DirectX::XMFLOAT4X4 mProj;
	DirectX::XMFLOAT4 mCameraPosition;
	DirectX::XMFLOAT4 mColour;
	float time;
	DirectX::XMFLOAT3 padding;
};

struct DirectionalLightCB
{
	DirectX::XMFLOAT3 direction;
	DirectX::XMFLOAT4 colour;
	float padding;
};

struct PointLightCB
{
	DirectX::XMFLOAT4 position;
	DirectX::XMFLOAT4 colour;
	float range;
	DirectX::XMFLOAT3 padding;
};

struct LightingBuffer
{
	int numDirLights;
	DirectionalLightCB dirLights[2];

	int numPointLights;
	PointLightCB pointLights[5];
	DirectX::XMFLOAT2 padding;
};

