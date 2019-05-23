#pragma once
#include "ISystem.h"
#include "ECSManager.h"
#include "wrl.h"
#include "ResourceManager.h"
#include "Vector4.h"
#include "Components.h"

class AudioSystem : public ISystem
{
protected:
	AudioSystem(const std::vector<int>& pMasks);

	std::shared_ptr<ECSManager> mEcsManager = ECSManager::Instance();
	std::shared_ptr<ResourceManager>  mResourceManager = ResourceManager::Instance();

public:
	virtual ~AudioSystem() {};

	virtual HRESULT Init() = 0;
	virtual void Cleanup() = 0;

	virtual Sound* LoadAudio(const Entity& pEntity) = 0;
};
