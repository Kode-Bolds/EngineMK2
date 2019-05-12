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
	auto entity = find_if(mEntities.begin(), mEntities.end(), [&](const Entity& entity) {return entity.ID == pEntity.ID; });

	if ((pEntity.componentMask & mMask) == mMask)
	{
		//If entity is not already assigned to this system add it to list
		if (entity == mEntities.end())
		{
			mEntities.push_back(pEntity);
		}
		//If entity is already assigned to this system update it's mask
		else
		{
			entity->componentMask = pEntity.componentMask;
		}
	}
	//If entity mask does not match system mask, remove from list
	else
	{
		mEntities.erase(remove_if(mEntities.begin(), mEntities.end(), [&](const Entity& entity) {return entity.ID == pEntity.ID; }), mEntities.end());
	}
}

/// <summary>
/// 
/// </summary>
void MovementSystem::Process()
{
	for(const Entity& entity : mEntities)
	{		
		//Check if entity has gravity component
		if ((entity.componentMask & ComponentType::COMPONENT_GRAVITY) == ComponentType::COMPONENT_GRAVITY)
		{
			//Modify velocity by gravity acceleration
			mEcsManager->VelocityComp(entity.ID)->velocity.Y += mGravityAccel * mSceneManager->DeltaTime();
		}

		//Modify velocity by acceleration
		mEcsManager->VelocityComp(entity.ID)->velocity += mEcsManager->VelocityComp(entity.ID)->acceleration * mSceneManager->DeltaTime();

		//Clamp velocity magnitude to max speed of entity
		if (mEcsManager->VelocityComp(entity.ID)->velocity.Magnitude() > mEcsManager->VelocityComp(entity.ID)->maxSpeed)
		{
			mEcsManager->VelocityComp(entity.ID)->velocity.Clamp(mEcsManager->VelocityComp(entity.ID)->maxSpeed);
		}

		//Modify translation by velocity
		mEcsManager->TransformComp(entity.ID)->translation += mEcsManager->VelocityComp(entity.ID)->velocity * mSceneManager->DeltaTime();
	}
}
