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
	float padding;
	DirectX::XMFLOAT4 colour;
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
	float numDirLights;
	DirectX::XMFLOAT3 padding;
	DirectionalLightCB dirLights[2];

	float numPointLights;
	DirectX::XMFLOAT3 padding2;
	PointLightCB pointLights[20];
};

