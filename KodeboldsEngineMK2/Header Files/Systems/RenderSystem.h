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
	std::vector<const Entity> mLights;
	const Entity* mActiveCamera;

public:
	explicit RenderSystem(const HWND& pWindow);
	virtual ~RenderSystem();

	void AssignEntity(const Entity& pEntity) override;
	void Process() override;
};