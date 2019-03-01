#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <string>

class RenderSystem;

class Texture
{
protected:
	Texture() {};
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTexture;

public:
	virtual ~Texture() {};

	virtual HRESULT Create(const RenderSystem* pRenderer, const std::string & pFilename) = 0;
	virtual Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> TextureRV() = 0;
};