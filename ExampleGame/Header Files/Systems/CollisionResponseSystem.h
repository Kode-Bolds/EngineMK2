#pragma once
#include "ECSManager.h"
#include "ISystem.h"
#include "CustomCollisionMask.h"
#include "KodeboldsMath.h"
#include "EntitySpawner.h"

class CollisionResponseSystem : public ISystem
{
private:
	std::shared_ptr<ECSManager> mEcsManager = ECSManager::Instance();

public:
	CollisionResponseSystem();
	virtual ~CollisionResponseSystem();

	void AssignEntity(const Entity& pEntity) override;
	void ReAssignEntity(const Entity& pEntity) override;
	void Process() override;
};