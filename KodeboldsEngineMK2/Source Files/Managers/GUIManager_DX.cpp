#include "GUIManager_DX.h"

void GUIManager_DX::Init(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const int pWidth, const int pHeight)
{
	mDevice = pDevice;
	mDeviceWidth = pWidth;
	mDeviceHeight = pHeight;

	mSpriteBatch = std::make_unique<DirectX::SpriteBatch>(pContext);

	LoadTextureFromFile(L"cat.png");

	Microsoft::WRL::ComPtr<ID3D11Texture2D> cat;
	mResource.As(&cat);

	CD3D11_TEXTURE2D_DESC catDesc;
	cat->GetDesc(&catDesc);

	mOrigin.x = float(catDesc.Width / 2);
	mOrigin.y = float(catDesc.Height / 2);

	mScreenPos.x = mDeviceWidth / 2.0f;
	mScreenPos.y = mDeviceHeight / 2.0f;

	mSpriteBatch->Begin();

	mSpriteBatch->Draw(mTexture.Get(), mScreenPos, nullptr, DirectX::Colors::White, 0.0f, mOrigin);

	mSpriteBatch->End();
}

void GUIManager_DX::LoadTextureFromFile(const wchar_t* pFileName)
{
	DirectX::CreateWICTextureFromFile(mDevice, pFileName, nullptr, mTexture.ReleaseAndGetAddressOf());
}

GUIManager_DX::~GUIManager_DX()
{
}

std::shared_ptr<GUIManager_DX> GUIManager_DX::Instance()
{
	static std::shared_ptr<GUIManager_DX> instance{ new GUIManager_DX };
	return instance;
}
