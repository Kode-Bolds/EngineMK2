#include "AntTweakManager.h"

/// <summary>
/// Default constructor
/// </summary>
AntTweakManager::AntTweakManager()
{
}

/// <summary>
/// Default destructor
/// </summary>
AntTweakManager::~AntTweakManager()
{
}

/// <summary>
/// Creates a singleton instance of AntTweak Manager if one hasn't been created before
/// Returns pointer to the instance of AntTweak Manager
/// </summary>
/// <returns>Shared pointer to the AntTweak Manager instance</returns>
std::shared_ptr<AntTweakManager> AntTweakManager::Instance()
{
	static std::shared_ptr<AntTweakManager> instance{ new AntTweakManager };
	return instance;
}

/// <summary>
/// Initialises anttweak GUI
/// </summary>
/// <param name="graphicsAPI">Graphics API used in application</param>
/// <param name="pDevice">Pointer to graphics device</param>
/// <param name="width">Width of window</param>
/// <param name="height">Height of window</param>
void AntTweakManager::Init(const TwGraphAPI& pGraphicsAPI, void* const pDevice, const int pWidth, const int pHeight) const
{
	TwInit(pGraphicsAPI, pDevice);
	TwWindowSize(pWidth, pHeight);
}

/// <summary>
/// Adds a bar to the anttweak GUI
/// </summary>
/// <param name="barName">Name of bar to be added</param>
void AntTweakManager::AddBar(const std::string& pBarName)
{
	TwBar* newBar = TwNewBar(pBarName.c_str());
	mBars.emplace_back(std::make_pair(pBarName, newBar));
}

/// <summary>
/// Adds a variable to the anttweak GUI
/// </summary>
/// <param name="barName">Name of the bar to hold the variable</param>
/// <param name="variableName">Name of the variable to be added</param>
/// <param name="variableType">Type of the variable to be added</param>
/// <param name="variable">Pointer to the variable to be added</param>
/// <param name="behaviourDefinition">Anttweak behaviour definition string</param>
void AntTweakManager::AddVariable(const std::string& pBarName, const std::string& pVariableName, const TwType& pVariableType, const void* const pVariable, const std::string& pBehaviourDefinition)
{
	auto it = std::find_if(mBars.begin(), mBars.end(), [&](const std::pair<std::string, TwBar*> bar) { return bar.first == pBarName; });
	TwAddVarRO(it->second, pVariableName.c_str(), pVariableType, const_cast<void*>(pVariable), pBehaviourDefinition.c_str());
}

/// <summary>
/// Deletes a bar from the anttweak GUI
/// </summary>
/// <param name="barName">Name of bar to be deleted</param>
void AntTweakManager::DeleteBar(const std::string& pBarName)
{
	auto it = std::find_if(mBars.begin(), mBars.end(), [&](const std::pair<std::string, TwBar*> bar) { return bar.first == pBarName; });
	TwDeleteBar(it->second);
	mBars.erase(it);
}

/// <summary>
/// Refreshes and draws the anttweak GUI
/// </summary>
void AntTweakManager::Draw()
{
	for (auto& bar : mBars)
	{
		TwRefreshBar(bar.second);
	}
	TwDraw();
}

/// <summary>
/// Deletes all bars and de-allocates all memory assigned to anttweak
/// </summary>
void AntTweakManager::Cleanup() const
{
	TwDeleteAllBars();
	TwTerminate();
}

void AntTweakManager::InititialiseGUI(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const int pWidth, const int pHeight)
{
	mDevice = pDevice;
	mDeviceWidth = pWidth;
	mDeviceHeight = pHeight;
	mContext = pContext;

	mSpriteBatch = std::make_unique<DirectX::SpriteBatch>(pContext);

	//CoInitialize(NULL);
	LoadTextureFromFile(L"cat.png");


	//Microsoft::WRL::ComPtr<ID3D11Texture2D> cat;
	//mResource.As(&cat);

	//CD3D11_TEXTURE2D_DESC catDesc;
	//cat->GetDesc(&catDesc);

	//mOrigin.x = float(catDesc.Width / 2);
	//mOrigin.y = float(catDesc.Height / 2);

	mScreenPos.x = mDeviceWidth / 2.0f;
	mScreenPos.y = mDeviceHeight / 2.0f;

}
void AntTweakManager::Render()
{
	mSpriteBatch->Begin();

	mSpriteBatch->Draw(mTexture.Get(), mScreenPos, nullptr, DirectX::Colors::White, 0.0f, mOrigin);

	mSpriteBatch->End();
}
void AntTweakManager::LoadTextureFromFile(const wchar_t* pFileName)
{
	auto imageTest = DirectX::CreateWICTextureFromFile(mDevice.Get(), mContext.Get(), pFileName, nullptr, mTexture.GetAddressOf());

	if (imageTest == 0x80070002) // file not found
	{
		int i = 0;
	}
}
