#pragma once
#include "AntTweakBar.h"
#include <d3d11.h>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <WICTextureLoader.h>
#include <SpriteBatch.h>
#include <wrl.h>
#include "ResourceManager.h"
#include <CommonStates.h>


class GUIManager
{
private:
	std::shared_ptr<ResourceManager> mResourceManager = ResourceManager::Instance();

	std::vector<std::pair<std::string, TwBar*>> mBars;

	int mDeviceWidth;
	int mDeviceHeight;
	Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;

	std::unique_ptr<DirectX::SpriteBatch> mSpriteBatch;
	std::unique_ptr<DirectX::CommonStates> m_states;

	//Private constructor for singleton pattern
	GUIManager();

public:
	~GUIManager();
	enum class SpriteOrigin {
		CENTRE,
	};

	enum class SpritePosition {
		CENTRE_TOP,
		CENTRE_MIDDLE,
		CENTRE_BOTTOM
	};

	//Singleton pattern
	//Deleted copy constructor and assignment operator so no copies of the singleton instance can be made
	GUIManager(const GUIManager& pGUIManager) = delete;
	GUIManager& operator=(GUIManager const&) = delete;

	static std::shared_ptr<GUIManager> Instance();

	// Ant Tweak Bar
	void Init(const TwGraphAPI& pGraphicsAPI, void* const pDevice, const int pWidth, const int pHeight) const;
	void AddBar(const std::string& pBarName);
	void AddVariable(const std::string& pBarName, const std::string& pVariableName, const TwType& pVariableType, const void* const pVariable, const std::string& pBehaviourDefinition);
	void DeleteBar(const std::string& pBarName);
	void Draw();
	void Cleanup() const;

	// Standard GUI
	void InititialiseGUI(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const int pWidth, const int pHeight);
	void Render();

	void LoadSprite(const wchar_t* pFileName, KodeboldsMath::Vector2 pOrigin, KodeboldsMath::Vector2 pPosition, float pRotation, float pScale);
	void LoadSprite(const wchar_t* pFileName, KodeboldsMath::Vector2 pOrigin, SpritePosition pPosition, float pRotation, float pScale);
	void LoadSprite(const wchar_t* pFileName, SpriteOrigin pOrigin, KodeboldsMath::Vector2 pPosition, float pRotation, float pScale);
	void LoadSprite(const wchar_t* pFileName, SpriteOrigin pOrigin, SpritePosition pPosition, float pRotation, float pScale);

};