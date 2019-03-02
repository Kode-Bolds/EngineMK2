#include "ResourceManager.h"


using namespace std;

//TODO: Test singleton pattern works

ResourceManager::ResourceManager() = default;
ResourceManager::~ResourceManager() = default;

const VBO* ResourceManager::LoadGeometry(const std::wstring& pFilename, const RenderSystem* pRenderer)
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
	newGeometry->Create(pRenderer, pFilename);
	//add it to the map
	mGeometries.emplace_back(make_pair(pFilename, newGeometry));
	//return the last thing in the dictionary (the newly created geometry)
	return mGeometries.end()->second;
}

HRESULT CompileShaderFromFile(const WCHAR * const pFileName, const LPCSTR pEntryPoint, const LPCSTR pShaderModel, ID3DBlob** const pBlobOut)
{
	auto hr{ S_OK };

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;

	// Disable optimizations to further improve shader debugging
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif



	ID3DBlob* errorBlob = nullptr;
	hr = D3DCompileFromFile(pFileName, nullptr, nullptr, pEntryPoint, pShaderModel,
		dwShaderFlags, 0, pBlobOut, &errorBlob);
	if (FAILED(hr))
	{
		if (errorBlob)
		{
			OutputDebugStringA(reinterpret_cast<const char*>(errorBlob->GetBufferPointer()));
			errorBlob->Release();
		}
		return hr;
	}
	if (errorBlob) errorBlob->Release();

	return hr;
}

std::shared_ptr<ResourceManager> ResourceManager::Instance()
{
	static shared_ptr<ResourceManager> instance{ new ResourceManager };
	return instance;
}
