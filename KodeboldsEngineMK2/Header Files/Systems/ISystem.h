#pragma once
#include <vector>
#include "Components.h"
#include "Entity.h"

class ISystem
{
private:
	std::vector<Entity> mEntities;
	ComponentType mMask;

public:
	virtual void Process() = 0;
	virtual void AssignEntity(const int& pEntity) = 0;
	virtual void RemoveEntity(const int& pEntity) = 0;
};