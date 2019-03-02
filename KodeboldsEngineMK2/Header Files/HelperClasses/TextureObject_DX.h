#pragma once
#include "TextureObject.h"
#include "DDSTextureLoader.h"
#include "RenderSystem.h"

class TextureObject_DX :
	public TextureObject
{
public:
	TextureObject_DX();
	virtual ~TextureObject_DX();

	HRESULT Create(const RenderSystem* pRenderer, const std::wstring& pFilename) override;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Texture() override;
};