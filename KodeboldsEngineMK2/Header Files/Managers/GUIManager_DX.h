#pragma once
#include "GUIManager.h"
#include <wrl.h>
#include <WICTextureLoader.h>
#include <SpriteBatch.h>

class GUIManager_DX : public GUIManager {
private:
	//Private constructor for singleton pattern
	GUIManager_DX();

	void LoadTextureFromFile(const wchar_t* pFileName);

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTexture;

	int mDeviceWidth;
	int mDeviceHeight;
	ID3D11Device* mDevice;

	std::unique_ptr<DirectX::SpriteBatch> mSpriteBatch;
	DirectX::XMFLOAT2  mScreenPos;
	DirectX::XMFLOAT2 mOrigin;

	Microsoft::WRL::ComPtr<ID3D11Resource> mResource;
protected:
public:
	~GUIManager_DX();

	void Init(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const int pWidth, const int pHeight);
	//Singleton pattern
	//Deleted copy constructor and assignment operator so no copies of the singleton instance can be made
	GUIManager_DX(GUIManager_DX const&) = delete;
	GUIManager_DX& operator=(GUIManager_DX const&) = delete;
	static std::shared_ptr<GUIManager_DX> Instance();
};