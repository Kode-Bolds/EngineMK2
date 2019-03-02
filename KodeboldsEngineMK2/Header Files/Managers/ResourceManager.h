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

class RenderSystem;

class ResourceManager
{
	std::vector< std::pair< std::wstring, Microsoft::WRL::ComPtr< ID3D11ShaderResourceView >>> mTextures{};
	std::vector< std::pair< std::wstring, VBO*>> mGeometries{};
	std::vector< std::pair< std::wstring, std::pair< Microsoft::WRL::ComPtr< ID3D11VertexShader >, Microsoft::WRL::ComPtr< ID3D11PixelShader >>>> mShaders{};
	//std::vector< std::pair< std::wstring, Microsoft::WRL::ComPtr< ID3D11Buffer >>> mInstances{};
	//std::vector< std::pair< string, AUDIOBUFFER>> mSounds;
	ResourceManager();

public:
	~ResourceManager();

	ResourceManager(const ResourceManager& pResourceManager) = delete;
	ResourceManager& operator=(ResourceManager const&) = delete;

	Microsoft::WRL::ComPtr< ID3D11ShaderResourceView > LoadTexture(const std::string& pFilename);
	const VBO* LoadGeometry(const std::wstring& pFilename, const RenderSystem* pRenderer);
	//AUDIOBUFFER LoadAudio(string filename);
	std::pair< Microsoft::WRL::ComPtr< ID3D11VertexShader >, Microsoft::WRL::ComPtr< ID3D11PixelShader >> LoadShader(const std::string& pFilename);
	static HRESULT CompileShaderFromFile(const WCHAR * const pFileName, const LPCSTR pEntryPoint, const LPCSTR pShaderModel, ID3DBlob** const pBlobOut);
	static std::shared_ptr< ResourceManager > Instance();
};

