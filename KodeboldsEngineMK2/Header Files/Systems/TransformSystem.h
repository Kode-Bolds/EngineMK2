#pragma once
#include "ECSManager.h"
#include "SceneManager.h"
#include "ISystem.h"
#include "Vector4.h"

class TransformSystem : public ISystem
{
private:
	std::shared_ptr<ECSManager> mEcsManager = ECSManager::Instance();

	void CalculateTransform(const Entity& pEntity) const;
	void CalculateDirections(const Entity& pEntity) const;
	void ExtractTransform(const Entity& pEntity) const;

public:
	TransformSystem();
	~TransformSystem();

	void AssignEntity(const Entity& pEntity) override;
	void ReAssignEntity(const Entity& pEntity) override;
	void Process() override;
};