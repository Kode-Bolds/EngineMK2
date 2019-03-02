#pragma once
#include <windows.h>
#include "ECSManager.h"
#include "Components.h"
#include "ISystem.h"
#include "Vector4.h"
#include <d3d11shader.h>
#include <d3d11.h>
#include <d3d11_1.h>
#include <wrl.h>
#include <directxcolors.h>
#include "ResourceManager.h"

class RenderSystem : public ISystem
{
private:

	std::vector<Entity> mLights;
	HWND mWindow;
	UINT mWidth{};
	UINT mHeight{};
	std::shared_ptr<ECSManager> mEcsManager = ECSManager::Instance();
	std::shared_ptr<ResourceManager>  mResourceManager = ResourceManager::Instance();
	const Entity* mActiveCamera;

	/// <summary>
	/// DirectX pointers
	/// </summary>
	D3D_FEATURE_LEVEL mFeatureLevel = D3D_FEATURE_LEVEL_11_0;
	Microsoft::WRL::ComPtr<ID3D11Device> mDevice = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Device1> mDevice1 = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext1> mContext1 = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain = nullptr;
	Microsoft::WRL::ComPtr<IDXGISwapChain1> mSwapChain1 = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencil = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> mDepthStencilState = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mConstantBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mConstantBufferUniform = nullptr;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> mTexSampler = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> mDefaultRasterizerState = nullptr;

	HRESULT Init();
	HRESULT CreateDevice();
	HRESULT CreateSwapChain();
	HRESULT CreateRenderTarget();
	HRESULT CreateDepth();
	HRESULT CreateRasterizer();
	HRESULT CreateSampler();
	void CreateViewport() const;
	HRESULT CreateConstantBuffers();
	void Cleanup();

	void ClearView() const;
	void SwapBuffers() const;
	void LoadGeometry(const Entity& pEntity) const;
	void LoadShaders(const Entity& pEntity) const;
	void LoadTexture(const Entity& pEntity) const;
public:
	explicit RenderSystem(const HWND& pWindow);
	virtual ~RenderSystem();


	void AssignEntity(const Entity& pEntity) override;
	void Process() override;
	Microsoft::WRL::ComPtr<ID3D11Device> Device() const { return mDevice; }
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> Context() const { return mContext; }

};
