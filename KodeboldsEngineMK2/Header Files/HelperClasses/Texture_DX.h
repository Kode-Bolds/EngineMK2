#pragma once
#include "Texture.h"
#include "DDSTextureLoader.h"

class Texture_DX :
	public Texture
{
public:
	Texture_DX();
	virtual ~Texture_DX();

	HRESULT Create(const RenderSystem* pRenderer, const std::string & pFilename) override;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> TextureRV() override;
};