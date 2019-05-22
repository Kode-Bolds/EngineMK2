#include "MovementSystem.h"

/// <summary>
/// Constructor
/// Initialises entity vector to max entities size
/// </summary>
MovementSystem::MovementSystem() 
	: ISystem(std::vector<int>{ComponentType::COMPONENT_TRANSFORM | ComponentType::COMPONENT_VELOCITY})
{
	mEntities = std::vector<Entity>(mEcsManager->MaxEntities(), Entity{ -1, ComponentType::COMPONENT_NONE });
}

/// <summary>
/// Default destructor
/// </summary>
MovementSystem::~MovementSystem()
{
}

/// <summary>
/// Assigns entity to system if the entities mask matches the system mask
/// </summary>
/// <param name="pEntity">Entity to be assigned</param>
void MovementSystem::AssignEntity(const Entity & pEntity)
{
	//Checks if entity mask matches the movement mask
	if ((pEntity.componentMask & mMasks[0]) == mMasks[0])
	{
		//Update entry in systems entity list
		mEntities[pEntity.ID] = pEntity;
	}
}

/// <summary>
/// Re-assigns entity to system when component is removed from entity
/// </summary>
/// <param name="pEntity">Entity to re-assign</param>
void MovementSystem::ReAssignEntity(const Entity & pEntity)
{
	//Checks if entity mask matches the movement mask
	if ((pEntity.componentMask & mMasks[0]) == mMasks[0])
	{
		//If the entity matches movement mask then update entry in systems entity list
		mEntities[pEntity.ID] = pEntity;
	}
	else
	{
		//If the mask doesn't match then set ID to -1
		mEntities[pEntity.ID].ID = -1;
	}
}

/// <summary>
/// Systems process function, core logic of system
/// Calculates entities velocity by applying the entities acceleration as well as acceleration of gravity
/// Applies velocity to entities transform
/// </summary>
void MovementSystem::Process()
{
	for (const Entity& entity : mEntities)
	{
		if (entity.ID != -1)
		{
			//Check if entity has gravity component
			if ((entity.componentMask & ComponentType::COMPONENT_GRAVITY) == ComponentType::COMPONENT_GRAVITY)
			{
				//Modify velocity by gravity acceleration
				mEcsManager->VelocityComp(entity.ID)->velocity.Y += mGravityAccel * static_cast<float>(mSceneManager->DeltaTime());
			}

			//Modify velocity by acceleration
			mEcsManager->VelocityComp(entity.ID)->velocity += mEcsManager->VelocityComp(entity.ID)->acceleration * static_cast<float>(mSceneManager->DeltaTime());

			//Clamp velocity magnitude to max speed of entity
			if (mEcsManager->VelocityComp(entity.ID)->velocity.Magnitude() > mEcsManager->VelocityComp(entity.ID)->maxSpeed)
			{
				mEcsManager->VelocityComp(entity.ID)->velocity.Clamp(mEcsManager->VelocityComp(entity.ID)->maxSpeed);
			}

			//Modify translation and transform by velocity
			mEcsManager->TransformComp(entity.ID)->translation += mEcsManager->VelocityComp(entity.ID)->velocity * static_cast<float>(mSceneManager->DeltaTime());
			mEcsManager->TransformComp(entity.ID)->transform *= KodeboldsMath::TranslationMatrix(mEcsManager->VelocityComp(entity.ID)->velocity * static_cast<float>(mSceneManager->DeltaTime()));

			//Modify the entities box collider bounds
			if (mEcsManager->BoxColliderComp(entity.ID))
			{
				mEcsManager->BoxColliderComp(entity.ID)->minBounds += (mEcsManager->VelocityComp(entity.ID)->velocity * static_cast<float>(mSceneManager->DeltaTime())).XYZ();
				mEcsManager->BoxColliderComp(entity.ID)->maxBounds += (mEcsManager->VelocityComp(entity.ID)->velocity * static_cast<float>(mSceneManager->DeltaTime())).XYZ();
			}
			if (mEcsManager->SphereColliderComp(entity.ID))
			{

			}
		}
	}
}
