#include "TextureObject_DX.h"

/// <summary>
/// 
/// </summary>
TextureObject_DX::TextureObject_DX()
{
}

/// <summary>
/// 
/// </summary>
TextureObject_DX::~TextureObject_DX()
{
}

/// <summary>
/// 
/// </summary>
/// <param name="pRenderer"></param>
/// <param name="pFilename"></param>
/// <returns></returns>
HRESULT TextureObject_DX::Create(const RenderSystem* pRenderer, const std::wstring& pFilename)
{
	HRESULT hr = S_OK;

	//Create shader resource for texture from file and store pointer to it
	hr = DirectX::CreateDDSTextureFromFile(pRenderer->Device(), pFilename, nullptr, &mTexture);
	if (FAILED(hr))
		return hr;

	return hr;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> TextureObject_DX::Texture()
{
	return mTexture;
}
