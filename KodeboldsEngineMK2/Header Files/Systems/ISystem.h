#pragma once
#include <vector>
#include "Components.h"
#include "Entity.h"

class ISystem
{
protected:
	std::vector<Entity> mEntities;
	std::vector<int> mMasks;
	ISystem(const std::vector<int>& pMasks) : mMasks(pMasks) {};

public:
	virtual ~ISystem() {};
	virtual void Process() = 0;
	virtual void AssignEntity(const Entity& pEntity) = 0;
	virtual void ReAssignEntity(const Entity& pEntity) = 0;
};