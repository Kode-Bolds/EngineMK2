#include "ResourceManager.h"


using namespace std;

//TODO: Test singleton pattern works

ResourceManager::ResourceManager() = default;
ResourceManager::~ResourceManager() = default;

const TextureObject * const ResourceManager::LoadTexture(const RenderSystem_DX * const pRenderer, const std::wstring & pFilename)
{
	auto hr{ S_OK };
	//find and return from map
	for (const auto& pair : mTextures)
	{
		if (pair.first == pFilename)
		{
			return pair.second;
		}
	}
	//else create a new texture
	TextureObject_DX* newTexture{};
	hr = newTexture->Create(pRenderer, pFilename);

	if (FAILED(hr))
	{
		return nullptr;
	}

	//add it to the map
	mTextures.emplace_back(make_pair(pFilename, newTexture));
	//return the last thing in the dictionary (the newly created texture)
	return mTextures.end()->second;
}

const VBO * const ResourceManager::LoadGeometry(const RenderSystem_DX * const pRenderer, const std::wstring& pFilename)
{
	auto hr{ S_OK };
	//find and return from map
	for (const auto& pair : mGeometries)
	{
		if (pair.first == pFilename)
		{
			return pair.second;
		}
	}
	//else create a new geometry
	VBO_DX* newGeometry{};
	hr = newGeometry->Create(pRenderer, pFilename);
	if (FAILED(hr))
	{
		return nullptr;
	}
	//add it to the map
	mGeometries.emplace_back(make_pair(pFilename, newGeometry));
	//return the last thing in the dictionary (the newly created geometry)
	return mGeometries.end()->second;
}

const ShaderObject * const ResourceManager::LoadShader(const RenderSystem_DX * const pRenderer, const std::wstring & pFilename)
{
	auto hr{ S_OK };
	//find and return from map
	for (const auto& pair : mShaders)
	{
		if (pair.first == pFilename)
		{
			return pair.second;
		}
	}
	//else create a new shader
	ShaderObject_DX* newShader{};
	hr = newShader->CreateVertex(pRenderer, pFilename, "VS", "vs_5_0");
	if (FAILED(hr))
	{
		return nullptr;
	}
	hr = newShader->CreatePixel(pRenderer, pFilename, "PS", "ps_5_0");
	if (FAILED(hr))
	{
		return nullptr;
	}
	//add it to the map
	mShaders.emplace_back(make_pair(pFilename, newShader));
	//return the last thing in the dictionary (the newly created shader)
	return mShaders.end()->second;
}

std::shared_ptr<ResourceManager> ResourceManager::Instance()
{
	static shared_ptr<ResourceManager> instance{ new ResourceManager };
	return instance;
}
