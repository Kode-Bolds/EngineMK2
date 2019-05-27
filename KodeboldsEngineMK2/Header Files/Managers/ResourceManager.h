#pragma once
#include <memory>
#include <vector>
#include <string>
#include "ObjLoader.h"
#include <wrl/client.h>
#include "VBO_DX.h"
#include "ShaderObject_DX.h"
#include "TextureObject_DX.h"
#include "ShaderObject_GL.h"
#include "TextureObject_GL.h"
#include "Sound_DX.h"
#include "Sound_GL.h"
#include "ECSManager.h"
#include "Sprite.h"
#include "Button.h"

class RenderSystem;

class ResourceManager
{
	std::vector< std::pair< std::wstring, TextureObject*>> mTextures{};
	std::vector< std::pair< std::wstring, VBO*>> mGeometries{};
	std::vector< std::pair< std::wstring, ShaderObject*>> mShaders{};
	//std::vector< std::pair< std::wstring, Microsoft::WRL::ComPtr< ID3D11Buffer >>> mInstances{};
	std::vector<std::pair<std::wstring, Sound*>> mSounds;

	//Private constructor for singleton pattern
	ResourceManager();

public:
	~ResourceManager();

	std::vector<std::pair<std::wstring, Sprite>> mSprites{};
	std::vector<std::pair<std::wstring, Button>> mButtons{};

	//Singleton pattern
	//Deleted copy constructor and assignment operator so no copies of the singleton instance can be made
	ResourceManager(const ResourceManager& pResourceManager) = delete;
	ResourceManager& operator=(ResourceManager const&) = delete;

	const TextureObject* const LoadTexture(const RenderSystem* const pRenderer, const std::wstring& pFilename);
	VBO* const LoadGeometry(const RenderSystem* const pRenderer, const std::wstring& pFilename);
	const Sound* const LoadAudio(const AudioSystem* const pAudioSystem, std::wstring& pFileName);
	const ShaderObject* const LoadShader(const RenderSystem* const pRenderer, const std::wstring& pFilename);


	static std::shared_ptr< ResourceManager > Instance();
};

