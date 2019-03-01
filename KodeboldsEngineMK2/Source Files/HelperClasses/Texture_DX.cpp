#include "Texture_DX.h"

Texture_DX::Texture_DX()
{
}

Texture_DX::~Texture_DX()
{
}

HRESULT Texture_DX::Create(const RenderSystem* pRenderer, const std::string & pFilename)
{
	HRESULT hr = S_OK;

	//Create texture from file
	hr = DirectX::CreateDDSTextureFromFile(pRenderer->Device(), pFilename, nullptr, &mTexture);
	if (FAILED(hr))
		return hr;

	return hr;
}

Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> Texture_DX::TextureRV()
{
	return mTexture;
}
