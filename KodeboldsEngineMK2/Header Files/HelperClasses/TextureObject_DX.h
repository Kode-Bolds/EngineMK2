#pragma once
#include "TextureObject.h"
#include "DDSTextureLoader.h"
#include <wrl.h>
#include <d3d11.h>

class RenderSystem;

class TextureObject_DX :
	public TextureObject
{
private:
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> mTextures;

public:
	TextureObject_DX();
	virtual ~TextureObject_DX();

	HRESULT Create(const RenderSystem* pRenderer, const std::vector<std::wstring>& pFilenames) override;
	void Load(const RenderSystem* pRenderer) override;
};