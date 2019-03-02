#pragma once
#include "TextureObject_DX.h"
#include "RenderSystem.h"

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
HRESULT TextureObject_DX::Create(const RenderSystem* pRenderer, const std::vector<std::wstring>& pFilenames)
{
	HRESULT hr = S_OK;

	if (!pFilenames[0].empty())
	{
		//Create shader resource for diffuse texture from file and store pointer to it
		hr = DirectX::CreateDDSTextureFromFile(pRenderer->Device().Get(), pFilenames[0].c_str(), nullptr, mTextures[0].GetAddressOf());
		if (FAILED(hr))
		{
			return hr;
		}
	}

	if (!pFilenames[1].empty())
	{
		//Create shader resource for normal map texture from file and store pointer to it
		hr = DirectX::CreateDDSTextureFromFile(pRenderer->Device().Get(), pFilenames[1].c_str(), nullptr, mTextures[1].GetAddressOf());
		if (FAILED(hr))
		{
			return hr;
		}
	}

	if (!pFilenames[2].empty())
	{
		//Create shader resource for height map texture from file and store pointer to it
		hr = DirectX::CreateDDSTextureFromFile(pRenderer->Device().Get(), pFilenames[2].c_str(), nullptr, mTextures[2].GetAddressOf());
		if (FAILED(hr))
		{
			return hr;
		}
	}

	return hr;
}

/// <summary>
/// 
/// </summary>
/// <param name="pRenderer"></param>
void TextureObject_DX::Load(const RenderSystem * pRenderer)
{
	pRenderer->Context()->PSSetShaderResources(0, 1, mTextures[0].GetAddressOf());
	pRenderer->Context()->PSSetShaderResources(1, 1, mTextures[1].GetAddressOf());
	pRenderer->Context()->PSSetShaderResources(2, 1, mTextures[2].GetAddressOf());
}
