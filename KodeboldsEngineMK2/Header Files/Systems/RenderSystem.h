#pragma once
#include <windows.h>
#include "ECSManager.h"
#include "Components.h"
#include "ISystem.h"
#include "Vector3.h"

class RenderSystem : public ISystem
{
private:
	std::shared_ptr<ECSManager> ecsManager = ECSManager::Instance();
	std::vector<Light> mLights;
	std::shared_ptr<Camera> mActiveCamera;

public:
	RenderSystem(const HWND& pWindow);
	virtual ~RenderSystem();

	void AssignEntity(const Entity& pEntity) override;
	//void RemoveEntity(const int& pEntityID) override;
	void Process() override;
};