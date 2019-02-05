#pragma once
#include <vector>
#include "ComponentType.h"

class ISystem
{
private:
	std::vector<int> mEntities;
	ComponentType mMask;

public:
	virtual void Process() = 0;
	virtual void AssignEntity(const int& pEntity) = 0;
	virtual void RemoveEntity(const int& pEntity) = 0;
};