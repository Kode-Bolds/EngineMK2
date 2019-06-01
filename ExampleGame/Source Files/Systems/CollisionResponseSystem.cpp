#include "CollisionResponseSystem.h"

/// <summary>
/// 
/// </summary>
CollisionResponseSystem::CollisionResponseSystem()
	: ISystem(std::vector<int>{ComponentType::COMPONENT_COLLISION})
{
	mEntities = std::vector<Entity>(mEcsManager->MaxEntities(), Entity{ -1, ComponentType::COMPONENT_NONE });
}

/// <summary>
/// 
/// </summary>
CollisionResponseSystem::~CollisionResponseSystem()
{
}

/// <summary>
/// 
/// </summary>
/// <param name="pEntity"></param>
void CollisionResponseSystem::AssignEntity(const Entity & pEntity)
{
	//Checks if entity mask matches the collision mask
	if ((pEntity.componentMask & mMasks[0]) == mMasks[0])
	{
		//Update entry in systems entity list
		mEntities[pEntity.ID] = pEntity;
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="pEntity"></param>
void CollisionResponseSystem::ReAssignEntity(const Entity & pEntity)
{
	//Checks if entity mask matches the collision mask
	if ((pEntity.componentMask & mMasks[0]) == mMasks[0])
	{
		//If the entity matches collision mask then update entry in systems entity list
		mEntities[pEntity.ID] = pEntity;
	}
	else
	{
		//If the mask doesn't match then set ID to -1
		mEntities[pEntity.ID].ID = -1;
	}
}

/// <summary>
/// 
/// </summary>
void CollisionResponseSystem::Process()
{
	for (const Entity& entity : mEntities)
	{
		if (entity.ID != -1)
		{
			int entityMask = 0;
			Collision* collision = mEcsManager->CollisionComp(entity.ID);
			if (collision)
			{
				if (!collision->handled)
				{
					//Retrieve the entity mask from the box collider if it has one
					if (BoxCollider* b = mEcsManager->BoxColliderComp(entity.ID))
						entityMask = b->collisionMask;

					//Retrieve the entity mask from the sphere collider if it has one
					if (SphereCollider* s = mEcsManager->SphereColliderComp(entity.ID))
						entityMask = s->collisionMask;

					//If the player collides with the floor, remove gravity and set Y velocity to 0
					if (entityMask == CustomCollisionMask::PLAYER && collision->collidedEntityCollisionMask == CustomCollisionMask::FLOOR)
					{
						if (mEcsManager->GravityComp(entity.ID))
						{
							mEcsManager->RemoveGravityComp(entity.ID);
							mEcsManager->VelocityComp(entity.ID)->velocity.Y = 0;
							mEcsManager->RemoveGravityComp(entity.ID + 1);
							mEcsManager->VelocityComp(entity.ID + 1)->velocity.Y = 0;
							mEcsManager->RemoveGravityComp(entity.ID + 2);
							mEcsManager->VelocityComp(entity.ID + 2)->velocity.Y = 0;
						}
						mEcsManager->CollisionComp(entity.ID)->handled = true;
						mEcsManager->CollisionComp(mEcsManager->CollisionComp(entity.ID)->collidedEntity)->handled = true;
					}

					//If asteroid collides with the player, move the asteroid
					if (entityMask == CustomCollisionMask::ASTEROID && collision->collidedEntityCollisionMask == CustomCollisionMask::SHIP)
					{
						int player = mEcsManager->CollisionComp(entity.ID)->collidedEntity;

						//Get direction vector between the ship and asteroid
						KodeboldsMath::Vector4 direction = mEcsManager->TransformComp(entity.ID)->translation - mEcsManager->TransformComp(player)->translation;
						direction.Normalise();

						//Set the velocity of the asteroid to the velocity of the ship in the direction of the direction vector
						mEcsManager->VelocityComp(entity.ID)->velocity = (direction * mEcsManager->VelocityComp(player)->velocity.Magnitude()) * 0.9f;

						mEcsManager->CollisionComp(entity.ID)->handled = true;
						mEcsManager->CollisionComp(player)->handled = true;
					}

					//If asteroid collides with another asteroid, move the asteroids
					if (entityMask == CustomCollisionMask::ASTEROID && collision->collidedEntityCollisionMask == CustomCollisionMask::ASTEROID)
					{
						int collidedAsteroid = mEcsManager->CollisionComp(entity.ID)->collidedEntity;

						if (mEcsManager->VelocityComp(entity.ID)->velocity.Magnitude() != 0 && mEcsManager->TransformComp(collidedAsteroid))
						{
							//Get direction vector between the asteroids
							KodeboldsMath::Vector4 direction = mEcsManager->TransformComp(entity.ID)->translation - mEcsManager->TransformComp(collidedAsteroid)->translation;
							direction.Normalise();

							//Set the velocity of the asteroids
							mEcsManager->VelocityComp(collidedAsteroid)->velocity = (direction * mEcsManager->VelocityComp(entity.ID)->velocity.Magnitude()) * -0.9f;
							mEcsManager->VelocityComp(entity.ID)->velocity = (direction * mEcsManager->VelocityComp(collidedAsteroid)->velocity.Magnitude()) * 0.9f;

							mEcsManager->CollisionComp(entity.ID)->handled = true;
							mEcsManager->CollisionComp(collidedAsteroid)->handled = true;
						}
					}

					//If laser collides with asteroid, destroy both
					if (entityMask == CustomCollisionMask::SHIP_LASER && collision->collidedEntityCollisionMask == CustomCollisionMask::ASTEROID)
					{
						if (mEcsManager->CollisionComp(entity.ID))
						{
							const KodeboldsMath::Vector4 pos = mEcsManager->TransformComp(mEcsManager->CollisionComp(entity.ID)->collidedEntity)->translation;
							const float radius = mEcsManager->SphereColliderComp(mEcsManager->CollisionComp(entity.ID)->collidedEntity)->radius / 4;
							const KodeboldsMath::Vector4 scale = mEcsManager->TransformComp(mEcsManager->CollisionComp(entity.ID)->collidedEntity)->scale / 4;

							//Split asteroid into 4 smaller asteroids with an acceleration outwards of the translation of the destroyed asteroid
							int asteroid = EntitySpawner::SpawnAsteroid(pos + KodeboldsMath::Vector4(0, 0, 10, 0), scale, KodeboldsMath::Vector4(0, 0, 0, 1), radius, 0,
								CustomCollisionMask::ASTEROID, L"asteroid_diffuse.dds", L"asteroid_normal.dds");
							mEcsManager->VelocityComp(asteroid)->velocity = KodeboldsMath::Vector4(15, 0, 15, 1);

							asteroid = EntitySpawner::SpawnAsteroid(pos + KodeboldsMath::Vector4(0, 0, -10, 0), scale, KodeboldsMath::Vector4(0, 0, 0, 1), radius, 0,
								CustomCollisionMask::ASTEROID, L"asteroid_diffuse.dds", L"asteroid_normal.dds");
							mEcsManager->VelocityComp(asteroid)->velocity = KodeboldsMath::Vector4(0, 15, -15, 1);

							asteroid = EntitySpawner::SpawnAsteroid(pos + KodeboldsMath::Vector4(0, 10, 0, 0), scale, KodeboldsMath::Vector4(0, 0, 0, 1), radius, 0,
								CustomCollisionMask::ASTEROID, L"asteroid_diffuse.dds", L"asteroid_normal.dds");
							mEcsManager->VelocityComp(asteroid)->velocity = KodeboldsMath::Vector4(-15, 0, 15, 1);

							asteroid = EntitySpawner::SpawnAsteroid(pos + KodeboldsMath::Vector4(0, -10, 0, 0), scale, KodeboldsMath::Vector4(0, 0, 0, 1), radius, 0,
								CustomCollisionMask::ASTEROID, L"asteroid_diffuse.dds", L"asteroid_normal.dds");
							mEcsManager->VelocityComp(asteroid)->velocity = KodeboldsMath::Vector4(15, -15, 0, 1);

							//Destroy laser and asteroid
							mEcsManager->DestroyEntity(mEcsManager->CollisionComp(entity.ID)->collidedEntity);
							mEcsManager->DestroyEntity(entity.ID);
						}

						// TODO: INCREASE SCORE
					}
				}
			}
		}
	}
}
