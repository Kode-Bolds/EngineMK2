#pragma once
#include "ISystem.h"
#include "KodeboldsMath.h"
#include "ECSManager.h"

class TransformSystem : public ISystem
{
private:
	std::shared_ptr<ECSManager> mEcsManager = ECSManager::Instance();

	void CalculateTransform(const unsigned short pEntity);
	void CalculateDirections(const unsigned short pEntity);
	void ExtractTransformations(const unsigned short pEntity);

public:
	TransformSystem();
	virtual ~TransformSystem();

	void AssignEntity(const Entity& pEntity) override;
	void ReAssignEntity(const Entity& pEntity) override;
	void Process() override;
};