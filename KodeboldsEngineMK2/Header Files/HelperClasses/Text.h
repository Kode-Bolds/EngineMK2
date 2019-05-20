#pragma once
#include <wrl.h>
#include <d3d11.h>

class Text
{
public:
	const wchar_t* mText;
	DirectX::XMFLOAT2 mPosition;
	DirectX::XMFLOAT2 mOrigin;
	float mScale;
};