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
		//Check if entity has gravity component
		if ((entity.mComponentMask & ComponentType::COMPONENT_GRAVITY) == ComponentType::COMPONENT_GRAVITY)
		{
			//Modify acceleration by gravity
			ecsManager->VelocityComp(entity.mID).mAcceleration.y += -9.81; //Maybe make this something like 0.981 or similar to scale it down? Multiply by delta time from scene manager
		}

		//WRITE OWN VECTOR?? XMFLOAT and DirectXMath just make this code a mess, could condense everything below into two lines and an if statement if we had a custom vector 
		//that supported using += operator etc and a nicer method of getting the magnitude than the mess in the comments below instead of clamping each individual xyz value with 3 ifs

		//DirectX::XMVECTOR velocity = DirectX::XMLoadFloat3(&ecsManager->VelocityComp(entity.mID).mVelocity);
		//DirectX::XMFLOAT3 magnitude;
		//DirectX::XMStoreFloat3(&magnitude, DirectX::XMVector3Length(velocity));
		//float speed = magnitude.x;


		//Modify velocity by acceleration
		ecsManager->VelocityComp(entity.mID).mVelocity.x += ecsManager->VelocityComp(entity.mID).mAcceleration.x; //Multiply by delta time from scene manager
		ecsManager->VelocityComp(entity.mID).mVelocity.y += ecsManager->VelocityComp(entity.mID).mAcceleration.y;
		ecsManager->VelocityComp(entity.mID).mVelocity.z += ecsManager->VelocityComp(entity.mID).mAcceleration.z;

		//Clamp velocity xyz values to max speed of entity
		if (ecsManager->VelocityComp(entity.mID).mVelocity.x > ecsManager->VelocityComp(entity.mID).maxSpeed)
		{
			ecsManager->VelocityComp(entity.mID).mVelocity.x = ecsManager->VelocityComp(entity.mID).maxSpeed;
		}
		if (ecsManager->VelocityComp(entity.mID).mVelocity.y > ecsManager->VelocityComp(entity.mID).maxSpeed)
		{
			ecsManager->VelocityComp(entity.mID).mVelocity.y = ecsManager->VelocityComp(entity.mID).maxSpeed;
		}
		if (ecsManager->VelocityComp(entity.mID).mVelocity.z > ecsManager->VelocityComp(entity.mID).maxSpeed)
		{
			ecsManager->VelocityComp(entity.mID).mVelocity.z = ecsManager->VelocityComp(entity.mID).maxSpeed;
		}

		//Modify translation by velocity
		ecsManager->TransformComp(entity.mID).mTranslation.x += ecsManager->VelocityComp(entity.mID).mVelocity.x; //Multiply by delta time from scene manager
		ecsManager->TransformComp(entity.mID).mTranslation.y += ecsManager->VelocityComp(entity.mID).mVelocity.y;
		ecsManager->TransformComp(entity.mID).mTranslation.z += ecsManager->VelocityComp(entity.mID).mVelocity.z;
	}
}
