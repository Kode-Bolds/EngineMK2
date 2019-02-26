#pragma once
#include <memory>
#include <vector>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <string>
#include "ObjLoader.h"
#include <wrl/client.h>

class ResourceManager final
{
	std::vector< std::pair< std::string, Microsoft::WRL::ComPtr< ID3D11ShaderResourceView >>> mTextures{};
	std::vector< std::pair< std::string, std::pair< Microsoft::WRL::ComPtr< ID3D11Buffer >, Microsoft::WRL::ComPtr< ID3D11Buffer >>>> mGeometries{};
	std::vector< std::pair< std::string, Microsoft::WRL::ComPtr< ID3D11Buffer >>> mInstances{};
	std::vector< std::pair< std::string, std::pair< Microsoft::WRL::ComPtr< ID3D11VertexShader >, Microsoft::WRL::ComPtr< ID3D11PixelShader >>>> mShaders{};
	//std::vector< std::pair< string, AUDIOBUFFER>> mSounds;
	ResourceManager();

public:
	~ResourceManager();

	ResourceManager(const ResourceManager& pResourceManager) = delete;
	ResourceManager& operator=(ResourceManager const&) = delete;

	Microsoft::WRL::ComPtr< ID3D11ShaderResourceView > LoadTexture(const std::string& pFilename);
	std::pair< Microsoft::WRL::ComPtr< ID3D11Buffer >, Microsoft::WRL::ComPtr< ID3D11Buffer >> LoadGeometry(const std::string& pFilename);
	//AUDIOBUFFER LoadAudio(string filename);
	std::pair< Microsoft::WRL::ComPtr< ID3D11VertexShader >, Microsoft::WRL::ComPtr< ID3D11PixelShader >> LoadShader(const std::string& pFilename);
	static std::shared_ptr< ResourceManager > Instance();
};

