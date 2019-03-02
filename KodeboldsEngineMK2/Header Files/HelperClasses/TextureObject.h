#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <string>
#include "RenderSystem.h"

class TextureObject
{
protected:
	TextureObject() {};
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTexture;

public:
	virtual ~TextureObject() {};

	virtual HRESULT Create(const RenderSystem* pRenderer, const std::wstring& pFilename) = 0;
	virtual Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Texture() = 0;
};