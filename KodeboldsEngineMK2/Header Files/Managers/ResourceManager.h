#pragma once
#include <memory>
#include <vector>
#include <d3d11_1.h>

class ResourceManager final
{
	static std::shared_ptr<ResourceManager> mInstance;

	std::vector< std::pair< string, std::shared_ptr< ID3D11ShaderResourceView >>> mTextures{};
	std::vector< std::pair< string, std::pair< std::shared_ptr< ID3D11Buffer >, std::shared_ptr< ID3D11Buffer >>>> mGeometries{};
	std::vector< std::pair< string, std::shared_ptr< ID3D11Buffer >>> mInstances{};
	std::vector< std::pair< string, std::pair< std::shared_ptr< ID3D11VertexShader >, std::shared_ptr< ID3D11PixelShader >>>> mShaders{};
	//std::vector< std::pair< string, AUDIOBUFFER>> mSounds;

public:
	ResourceManager();
	~ResourceManager();

	static std::shared_ptr< ResourceManager > Instance();

	std::shared_ptr< ID3D11ShaderResourceView > LoadTexture(string filename);
	std::pair< std::shared_ptr< ID3D11Buffer >, std::shared_ptr< ID3D11Buffer >> LoadGeometry(string filename);
	//AUDIOBUFFER LoadAudio(string filename);
	std::pair< std::shared_ptr< ID3D11VertexShader >, std::shared_ptr< ID3D11PixelShader >> LoadShader(string filename);
};

