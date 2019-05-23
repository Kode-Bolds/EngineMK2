#pragma once
#include <windows.h>
#include <d3d11shader.h>
#include <d3d11.h>
#include <d3d11_1.h>
#include <wrl.h>
#include <directxcolors.h>
#include "RenderSystem.h"
#include "ConstantBuffer.h"

class RenderSystem_DX : public RenderSystem
{
private:
	std::vector<Entity> mPointLights;
	std::vector<Entity> mDirectionalLights;
	std::vector<Entity> mCameras;
	HWND mWindow;
	UINT mWidth{};
	UINT mHeight{};
	const Entity* mActiveCamera;
	VBO* mGeometry{};
	ConstantBuffer mCB{};
	LightingBuffer mLightCB{};

	std::wstring mActiveGeometry;
	std::wstring mActiveShader;
	BlendState mActiveBlend;
	CullState mActiveCull;
	DepthState mActiveDepth;

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
	Microsoft::WRL::ComPtr<ID3D11Buffer> mConstantBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mLightingBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> mTexSampler = nullptr;

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> mRastWireframeState = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> mRastNoCullState = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> mRastFrontCullState = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> mRastBackCullState = nullptr;

	Microsoft::WRL::ComPtr<ID3D11BlendState> mAlphaBlend = nullptr;
	Microsoft::WRL::ComPtr<ID3D11BlendState> mNoBlend = nullptr;

	Microsoft::WRL::ComPtr<ID3D11DepthStencilState>	mDepthNone = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState>	mDepthLessEqual = nullptr;

	HRESULT Init() override;
	HRESULT CreateDevice() override;
	HRESULT CreateSwapChain() override;
	HRESULT CreateRenderTarget() override;
	HRESULT CreateDepth() override;
	HRESULT CreateRasterizer() override;
	HRESULT CreateBlend() override;
	HRESULT CreateSampler() override;
	void CreateViewport() const override;
	HRESULT CreateConstantBuffers();
	void Cleanup() override;

	void ClearView() const override;
	void SwapBuffers() const override;
	void LoadGeometry(const Entity& pEntity) override;
	void LoadShaders(const Entity& pEntity) override;
	void LoadTexture(const Entity& pEntity) override;

	void SetViewProj() override;
	void SetLights() override;
	void SetCamera() override;



public:
	explicit RenderSystem_DX(const HWND& pWindow, const int pMaxLights);
	virtual ~RenderSystem_DX();


	void AssignEntity(const Entity& pEntity) override;
	void ReAssignEntity(const Entity& pEntity) override;
	void Process() override;
	Microsoft::WRL::ComPtr<ID3D11Device> Device() const { return mDevice; }
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> Context() const { return mContext; }

};
