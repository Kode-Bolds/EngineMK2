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
	if ((pEntity.mComponentMask & mMask) == mMask)
	{
		if (entity == mEntities.end())
		{
			mEntities.push_back(pEntity);
		}
		else
		{
			entity->mComponentMask = pEntity.mComponentMask;
		}
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
			//Modify velocity by gravity acceleration
			mEcsManager->VelocityComp(entity.mID)->mVelocity.Y() += gravityAccel * mSceneManager->DeltaTime();
		}

		//Modify velocity by acceleration
		mEcsManager->VelocityComp(entity.mID)->mVelocity += mEcsManager->VelocityComp(entity.mID)->mAcceleration * mSceneManager->DeltaTime();

		//Clamp velocity magnitude to max speed of entity
		if (mEcsManager->VelocityComp(entity.mID)->mVelocity.Magnitude() > mEcsManager->VelocityComp(entity.mID)->maxSpeed)
		{
			mEcsManager->VelocityComp(entity.mID)->mVelocity.Clamp(mEcsManager->VelocityComp(entity.mID)->maxSpeed);
		}

		//Modify translation by velocity
		mEcsManager->TransformComp(entity.mID)->mTranslation += mEcsManager->VelocityComp(entity.mID)->mVelocity * mSceneManager->DeltaTime();
	}
}
