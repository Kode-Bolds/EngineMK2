#pragma once
#include "ISystem.h"
#include "ECSManager.h"
#include "wrl.h"
#include "VBO.h"
#include "GUIManager.h"
#include "ResourceManager.h"
#include "Vector4.h"
#include "Components.h"
#include "SceneManager.h"

class RenderSystem : public ISystem
{
protected:
	RenderSystem(const std::vector<int>& pMasks, const int pMaxPointLight, const int pMaxDirLights);

	std::shared_ptr<GUIManager> mGUIManager = GUIManager::Instance();
	std::shared_ptr<ECSManager> mEcsManager = ECSManager::Instance();
	std::shared_ptr<ResourceManager>  mResourceManager = ResourceManager::Instance();
	std::shared_ptr<SceneManager> mSceneManager = SceneManager::Instance();

	int mMaxPointLights;
	int mMaxDirLights;

public:
	virtual ~RenderSystem() {};

	virtual HRESULT Init() = 0;
	virtual HRESULT CreateDevice() = 0;
	virtual HRESULT CreateSwapChain() = 0;
	virtual HRESULT CreateRenderTarget() = 0;
	virtual HRESULT CreateDepth() = 0;
	virtual HRESULT CreateRasterizer() = 0;
	virtual HRESULT CreateBlend() = 0;
	virtual HRESULT CreateSampler() = 0;
	virtual void CreateViewport() const = 0;
	virtual void Cleanup() = 0;

	virtual void ClearView() const = 0;
	virtual void SwapBuffers() const = 0;
	virtual void LoadGeometry(const Entity& pEntity) = 0;
	virtual void LoadShaders(const Entity& pEntity) = 0;
	virtual void LoadTexture(const Entity& pEntity) = 0;
	virtual void SetViewProj() = 0;
	virtual void SetLights() = 0;
	virtual void SetCamera() = 0;
};
