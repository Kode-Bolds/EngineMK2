#include "MovementSystem.h"

/// <summary>
/// 
/// </summary>
MovementSystem::MovementSystem() : ISystem(ComponentType::COMPONENT_TRANSFORM | ComponentType::COMPONENT_VELOCITY)
{
}

/// <summary>
/// 
/// </summary>
MovementSystem::~MovementSystem()
{
}

/// <summary>
/// 
/// </summary>
/// <param name="pEntity"></param>
void MovementSystem::AssignEntity(const Entity & pEntity)
{
	//Finds if an entity that matches given entities ID exists and returns it
	auto entity = find_if(mEntities.begin(), mEntities.end(), [&](const Entity& entity) {return entity.mID == pEntity.mID; });
	if (entity == mEntities.end() && (pEntity.mComponentMask & mMask) == mMask)
	{
		mEntities.push_back(pEntity);
	}
	else
	{
		mEntities.erase(remove_if(mEntities.begin(), mEntities.end(), [&](const Entity& entity) {return entity.mID == pEntity.mID; }), mEntities.end());
	}
}

/// <summary>
/// 
/// </summary>
void MovementSystem::Process()
{
	for(Entity& entity : mEntities)
	{		
		//Check if entity has gravity component
		if ((entity.mComponentMask & ComponentType::COMPONENT_GRAVITY) == ComponentType::COMPONENT_GRAVITY)
		{
			//Modify acceleration by gravity
			ecsManager->VelocityComp(entity.mID).mAcceleration.Y() += -9.81f; //Maybe make this something like 0.981 or similar to scale it down? Multiply by delta time from scene manager
		}

		//Modify velocity by acceleration
		ecsManager->VelocityComp(entity.mID).mVelocity += ecsManager->VelocityComp(entity.mID).mAcceleration; //Multiply by delta time from scene manager

		//Clamp velocity magnitude to max speed of entity
		if (ecsManager->VelocityComp(entity.mID).mVelocity.Magnitude() > ecsManager->VelocityComp(entity.mID).maxSpeed)
		{
			ecsManager->VelocityComp(entity.mID).mVelocity.Clamp(ecsManager->VelocityComp(entity.mID).maxSpeed);
		}

		//Modify translation by velocity
		ecsManager->TransformComp(entity.mID).mTranslation += ecsManager->VelocityComp(entity.mID).mVelocity; //Multiply by delta time from scene manager
	}
}
