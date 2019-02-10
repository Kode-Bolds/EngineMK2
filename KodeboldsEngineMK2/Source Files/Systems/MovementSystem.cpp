#include "MovementSystem.h"

MovementSystem::MovementSystem() : ISystem(ComponentType::COMPONENT_TRANSFORM | ComponentType::COMPONENT_VELOCITY)
{
}

MovementSystem::~MovementSystem()
{
}

void MovementSystem::AssignEntity(const Entity & pEntity)
{
	//Finds if an entity that matches given entities ID exists and returns it
	auto entity = find_if(mEntities.begin(), mEntities.end(), [&](const Entity& entity) {return entity.mID == pEntity.mID; });
	if (entity == mEntities.end())
	{
		if ((entity->mComponentMask & mMask) == mMask)
		{
			mEntities.push_back(*entity);
		}
	}
}

void MovementSystem::RemoveEntity(const int & pEntityID)
{
	mEntities.erase(remove_if(mEntities.begin(), mEntities.end(), [&](const Entity& entity) {return entity.mID == pEntityID; }));
}

void MovementSystem::Process()
{
	for(Entity entity : mEntities)
	{		
		//Modify acceleration by gravity if gravity component
		//Modify velocity (clamped by max speed) by acceleration
		//Modify translation by velocity
	}
}
