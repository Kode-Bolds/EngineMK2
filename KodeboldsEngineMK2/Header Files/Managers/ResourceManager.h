#pragma once
#include <memory>
#include <vector>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include "DDSTextureLoader.h"
#include <string>
#include "ObjLoader.h"
#include <wrl/client.h>
#include "VBO_DX.h"
#include "ShaderObject_DX.h"
#include "TextureObject_DX.h"

class RenderSystem_DX;

class ResourceManager
{
	std::vector< std::pair< std::wstring, TextureObject*>> mTextures{};
	std::vector< std::pair< std::wstring, VBO*>> mGeometries{};
	std::vector< std::pair< std::wstring, ShaderObject*>> mShaders{};
	//std::vector< std::pair< std::wstring, Microsoft::WRL::ComPtr< ID3D11Buffer >>> mInstances{};
	//std::vector< std::pair< string, AUDIOBUFFER>> mSounds;
	ResourceManager();

public:
	~ResourceManager();

	ResourceManager(const ResourceManager& pResourceManager) = delete;
	ResourceManager& operator=(ResourceManager const&) = delete;

	const TextureObject* LoadTexture(const RenderSystem_DX* pRenderer, const std::wstring& pFilename);
	const VBO* LoadGeometry(const RenderSystem_DX* pRenderer, const std::wstring& pFilename);
	//AUDIOBUFFER LoadAudio(string filename);
	const ShaderObject* LoadShader(const RenderSystem_DX* pRenderer, const std::wstring& pFilename);
	static std::shared_ptr< ResourceManager > Instance();
};

