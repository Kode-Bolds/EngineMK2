#pragma once
#include "ECSManager.h"
#include "Components.h"
#include "ISystem.h"
#include "Vector3.h"

class MovementSystem : public ISystem
{
private:
	std::shared_ptr<ECSManager> ecsManager = ECSManager::Instance();

public:
	MovementSystem();
	virtual ~MovementSystem();

	void AssignEntity(const Entity& pEntity) override;
	void RemoveEntity(const int& pEntityID) override;
	void Process() override;
};