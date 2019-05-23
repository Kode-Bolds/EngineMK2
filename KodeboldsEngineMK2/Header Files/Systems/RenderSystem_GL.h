#pragma once
#include <windows.h>
#include <wrl.h>
#include "RenderSystem.h"

class RenderSystem_GL : public RenderSystem
{
private:
	std::vector<Entity> mLights;
	HWND mWindow;
	UINT mWidth{};
	UINT height{};
	const Entity* mActiveCamera;
	VBO* mGeometry;

	std::wstring mActiveGeometry;
	std::wstring mActiveShader;

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
	VBO * const LoadGeometry(const Entity& pEntity) const override;
	void LoadShaders(const Entity& pEntity) const override;
	void LoadTexture(const Entity& pEntity) const override;

	void SetViewProj() override;
	void SetLights() override;

public:
	explicit RenderSystem_GL(const HWND& pWindow);
	virtual ~RenderSystem_GL();


	void AssignEntity(const Entity& pEntity) override;
	void ReAssignEntity(const Entity& pEntity) override;
	void Process() override;

};
