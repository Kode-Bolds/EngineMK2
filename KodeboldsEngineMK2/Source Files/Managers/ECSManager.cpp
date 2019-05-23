#include "ECSManager.h"
#include "RenderSystem_DX.h"

using namespace std;

/// <summary>
/// Assigns given entity to all appropriate systems upon addition of new component
/// </summary>
/// <param name="pEntity">The given entity to assign to systems</param>
void ECSManager::AssignEntity(const Entity & pEntity)
{
	mRenderSystem->AssignEntity(pEntity);

	for (auto & system : mUpdateSystems)
	{
		system->AssignEntity(pEntity);
	}
}

/// <summary>
/// Re-assigns given entity to all appropriate systems upon removal of component
/// </summary>
/// <param name="pEntity">Entity to re-assign</param>
void ECSManager::ReAssignEntity(const Entity & pEntity)
{
	mRenderSystem->ReAssignEntity(pEntity);

	for (auto & system : mUpdateSystems)
	{
		system->ReAssignEntity(pEntity);
	}
}

/// <summary>
/// Constructor for ECS Manager
/// Resizes entity and component vectors upon construction to max entities to avoid performance overhead of resizing
/// </summary>
ECSManager::ECSManager()
	:mEntityID(0), MAX_ENTITIES(65000)
{
	mEntities.reserve(MAX_ENTITIES);

	//Resize entity component map vectors
	mAIEntityMap.resize(MAX_ENTITIES);
	mAudioEntityMap.resize(MAX_ENTITIES);
	mBoxColliderEntityMap.resize(MAX_ENTITIES);
	mCameraEntityMap.resize(MAX_ENTITIES);
	mCollisionEntityMap.resize(MAX_ENTITIES);
	mColourEntityMap.resize(MAX_ENTITIES);
	mGeometryEntityMap.resize(MAX_ENTITIES);
	mGravityEntityMap.resize(MAX_ENTITIES);
	mPointLightEntityMap.resize(MAX_ENTITIES);
	mDirectionalLightEntityMap.resize(MAX_ENTITIES);
	mRayEntityMap.resize(MAX_ENTITIES);
	mShaderEntityMap.resize(MAX_ENTITIES);
	mSphereColliderEntityMap.resize(MAX_ENTITIES);
	mTextureEntityMap.resize(MAX_ENTITIES);
	mTransformEntityMap.resize(MAX_ENTITIES);
	mVelocityEntityMap.resize(MAX_ENTITIES);
}

/// <summary>
/// Default destructor
/// </summary>
ECSManager::~ECSManager()
{
}

/// <summary>
/// Creates a singleton instance of ECS Manager if one hasn't been created before
/// Returns pointer to the instance of ECS Manager
/// </summary>
/// <returns>Shared pointer to the ECS Manager instance</returns>
std::shared_ptr<ECSManager> ECSManager::Instance()
{
	static std::shared_ptr<ECSManager> instance{ new ECSManager };
	return instance;
}

/// <summary>
/// Get method for the rendering frequency
/// </summary>
/// <returns>Rendering frequency</returns>
int ECSManager::RenderingFrequency() const
{
	return mRenderingFrequency;
}

/// <summary>
/// Sets the maximum entity count for the ECS
/// </summary>
/// <param name="pEntityCount">Maximum entity count</param>
void ECSManager::SetMaxEntities(const int pEntityCount)
{
	MAX_ENTITIES = pEntityCount;
}

/// <summary>
/// Get method for the max entities value
/// </summary>
/// <returns>Max entities value</returns>
int ECSManager::MaxEntities() const
{
	return MAX_ENTITIES;
}

/// <summary>
/// Creates an entity with the given name
/// </summary>
int ECSManager::CreateEntity()
{
	unsigned short entityID = 0;
	if (!mFreeEntityIDs.empty())
	{
		entityID = mFreeEntityIDs.back();
		mFreeEntityIDs.pop_back();
		mEntities[entityID] = Entity{ entityID, ComponentType::COMPONENT_NONE };
	}
	else
	{
		mEntities.emplace_back(Entity{ mEntityID, ComponentType::COMPONENT_NONE });
		entityID = mEntityID;
		mEntityID++;
	}
	return entityID;
}

/// <summary>
/// Destroys an entity with the given name and all components owned by it
/// </summary>
/// <param name="pEntityID">Given id of the entity to delete</param>
void ECSManager::DestroyEntity(const int pEntityID)
{
	//Find entity with matching ID
	Entity* entity = &mEntities[pEntityID];

	//Removes all components owned by this entity
	//AI Comp
	if ((entity->componentMask & ComponentType::COMPONENT_AI) == ComponentType::COMPONENT_AI)
	{
		RemoveAIComp(pEntityID);
	}
	//Audio Comp
	if ((entity->componentMask & ComponentType::COMPONENT_AUDIO) == ComponentType::COMPONENT_AUDIO)
	{
		RemoveAudioComp(pEntityID);
	}
	//BoxCollider Comp
	if ((entity->componentMask & ComponentType::COMPONENT_BOXCOLLIDER) == ComponentType::COMPONENT_BOXCOLLIDER)
	{
		RemoveBoxColliderComp(pEntityID);
	}
	//Camera Comp
	if ((entity->componentMask & ComponentType::COMPONENT_CAMERA) == ComponentType::COMPONENT_CAMERA)
	{
		RemoveCameraComp(pEntityID);
	}
	//Collision Comp
	if ((entity->componentMask & ComponentType::COMPONENT_COLLISION) == ComponentType::COMPONENT_COLLISION)
	{
		RemoveCollisionComp(pEntityID);
	}
	//Colour Comp
	if ((entity->componentMask & ComponentType::COMPONENT_COLOUR) == ComponentType::COMPONENT_COLOUR)
	{
		RemoveColourComp(pEntityID);
	}
	//Geometry Comp
	if ((entity->componentMask & ComponentType::COMPONENT_GEOMETRY) == ComponentType::COMPONENT_GEOMETRY)
	{
		RemoveGeometryComp(pEntityID);
	}
	//Gravity Comp
	if ((entity->componentMask & ComponentType::COMPONENT_GRAVITY) == ComponentType::COMPONENT_GRAVITY)
	{
		RemoveGravityComp(pEntityID);
	}
	//Point Light Comp
	if ((entity->componentMask & ComponentType::COMPONENT_POINTLIGHT) == ComponentType::COMPONENT_POINTLIGHT)
	{
		RemovePointLightComp(pEntityID);
	}
	//Directional Light Comp
	if ((entity->componentMask & ComponentType::COMPONENT_DIRECTIONALLIGHT) == ComponentType::COMPONENT_DIRECTIONALLIGHT)
	{
		RemoveDirectionalLightComp(pEntityID);
	}
	//Ray Comp
	if ((entity->componentMask & ComponentType::COMPONENT_RAY) == ComponentType::COMPONENT_RAY)
	{
		RemoveRayComp(pEntityID);
	}
	//Shader Comp
	if ((entity->componentMask & ComponentType::COMPONENT_SHADER) == ComponentType::COMPONENT_SHADER)
	{
		RemoveShaderComp(pEntityID);
	}
	//SphereCollider Comp
	if ((entity->componentMask & ComponentType::COMPONENT_SPHERECOLLIDER) == ComponentType::COMPONENT_SPHERECOLLIDER)
	{
		RemoveSphereColliderComp(pEntityID);
	}
	//Texture Comp
	if ((entity->componentMask & ComponentType::COMPONENT_TEXTURE) == ComponentType::COMPONENT_TEXTURE)
	{
		RemoveTextureComp(pEntityID);
	}
	//Transform Comp
	if ((entity->componentMask & ComponentType::COMPONENT_TRANSFORM) == ComponentType::COMPONENT_TRANSFORM)
	{
		RemoveTransformComp(pEntityID);
	}
	//Velocity Comp
	if ((entity->componentMask & ComponentType::COMPONENT_VELOCITY) == ComponentType::COMPONENT_VELOCITY)
	{
		RemoveVelocityComp(pEntityID);
	}

	//Remove custom components
	for (int i = 0; i < mCustomComponentTypes.size(); i++)
	{
		//If entity contains a component of this type
		if ((entity->componentMask & mCustomComponentMasks[i]) == mCustomComponentMasks[i])
		{
			//Retrieve vector that contains this component type and vector that contains this componenet types entity component map
			std::vector<unsigned short>* componentEntityMapVector = mCustomComponentEntityMaps[i];
			std::vector<ComponentType*>* componentVector = static_cast<std::vector<ComponentType*>*>(mCustomComponentVectors[i]);

			//Replace removed component with back element
			(*componentVector)[(*componentEntityMapVector)[pEntityID]] = componentVector->back();

			//Set new index of component in the entity component map		
			(*componentEntityMapVector)[componentVector->size() - 1] = (*componentEntityMapVector)[pEntityID];

			//Pop back element
			componentVector->pop_back();

			//Adjust entities mask to no longer contain mask of removed component
			entity->componentMask = entity->componentMask &= ~mCustomComponentMasks[i]; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
			ReAssignEntity(*entity);
		}
	}

	//Finds the entity with the matching ID and removes it from the entities vector
	mEntities[pEntityID] = Entity{};
	mFreeEntityIDs.push_back(pEntityID);
}

/// <summary>
/// Adds the given system to the update system vector
/// </summary>
/// <param name="pSystem">Pointer to the given system</param>
void ECSManager::AddUpdateSystem(shared_ptr<ISystem> pSystem)
{
	mUpdateSystems.push_back(pSystem);
}

/// <summary>
/// Adds the given system to the render system vector
/// </summary>
/// <param name="pSystem">Pointer to the given system</param>
void ECSManager::AddRenderSystem(shared_ptr<ISystem> pSystem)
{
	if (!mRenderSystem)
	{
		mRenderSystem = pSystem;
	}
}

/// <summary>
/// Calls the process method for all systems in the ECS
/// </summary>
void ECSManager::ProcessSystems()
{
	//Run update systems
	for (auto & system : mUpdateSystems)
	{
		system->Process();
	}

	//If render task has already been assigned
	if (mRenderTask)
	{
		//Check if render task has been completed
		if (mRenderTask->IsDone())
		{
			//Calculate time taken
			mRenderFinish = std::chrono::high_resolution_clock::now();
			mRenderTime = mRenderFinish - mRenderStart;

			//Convert timings to milliseconds for frequency calculations
			const float renderTimeMilliseconds = static_cast<float>(mRenderTime.count() / pow(10, 6));

			//Calculate the actual rendering frequency
			mRenderingFrequency = static_cast<int>(1000 / renderTimeMilliseconds);

			//Cleanup then create new task and set start time
			mRenderTask->CleanUpTask();
			mRenderTask = mThreadManager->AddTask(std::bind(&ISystem::Process, mRenderSystem), nullptr, nullptr, std::vector<int>{0});
			mRenderStart = std::chrono::high_resolution_clock::now();
		}
	}
	else
	{
		//Create render task and set start time
		mRenderTask = mThreadManager->AddTask(std::bind(&ISystem::Process, mRenderSystem), nullptr, nullptr, std::vector<int>{0});
		mRenderStart = std::chrono::high_resolution_clock::now();
	}
}

/// <summary>
/// Adds an AI component to the entity with a given ID
/// </summary>
/// <param name="pAI">AI component to add</param>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::AddAIComp(const AI & pAI, const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	if (mAIFreeList.empty())
	{
		//Push onto back if no free slots and map to back
		mAIs.push_back(pAI);
		mAIEntityMap[pEntityID] = static_cast<unsigned short>(mAIs.size() - 1);
	}
	else
	{
		//Insert into free slot and map to free slot
		mAIs[mAIFreeList.back()] = pAI;
		mAIEntityMap[pEntityID] = static_cast<unsigned short>(mAIFreeList.back());
		mAIFreeList.pop_back();
	}

	//Adjust mask then assign entity
	entity->componentMask |= ComponentType::COMPONENT_AI;
	AssignEntity(*entity);
}

/// <summary>
/// Adds an Audio component to the entity with a given ID
/// </summary>
/// <param name="pAudio">Audio component to add</param>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::AddAudioComp(const Audio & pAudio, const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	if (mAudioFreeList.empty())
	{
		//Push onto back if no free slots and map to back
		mAudios.push_back(pAudio);
		mAudioEntityMap[pEntityID] = static_cast<unsigned short>(mAudios.size() - 1);
	}
	else
	{
		//Insert into free slot and map to free slot
		mAudios[mAudioFreeList.back()] = pAudio;
		mAudioEntityMap[pEntityID] = static_cast<unsigned short>(mAudioFreeList.back());
		mAudioFreeList.pop_back();
	}

	//Adjust mask then assign entity
	entity->componentMask |= ComponentType::COMPONENT_AUDIO;
	AssignEntity(*entity);
}

/// <summary>
/// Adds a Box Collider component to the entity with a given ID
/// </summary>
/// <param name="pBoxCollider">Box Collider component to add</param>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::AddBoxColliderComp(const BoxCollider & pBoxCollider, const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	if (mBoxColliderFreeList.empty())
	{
		//Push onto back if no free slots and map to back
		mBoxColliders.push_back(pBoxCollider);
		mBoxColliderEntityMap[pEntityID] = static_cast<unsigned short>(mBoxColliders.size() - 1);
	}
	else
	{
		//Insert into free slot and map to free slot
		mBoxColliders[mBoxColliderFreeList.back()] = pBoxCollider;
		mBoxColliderEntityMap[pEntityID] = static_cast<unsigned short>(mBoxColliderFreeList.back());
		mBoxColliderFreeList.pop_back();
	}

	//Adjust mask then assign entity
	entity->componentMask |= ComponentType::COMPONENT_BOXCOLLIDER;
	AssignEntity(*entity);
}

/// <summary>
/// Adds a Camera component to the entity with a given ID
/// </summary>
/// <param name="pCamera">Camera component to add</param>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::AddCameraComp(const Camera & pCamera, const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	if (mCameraFreeList.empty())
	{
		//Push onto back if no free slots and map to back
		mCameras.push_back(pCamera);
		mCameraEntityMap[pEntityID] = static_cast<unsigned short>(mCameras.size() - 1);
	}
	else
	{
		//Insert into free slot and map to free slot
		mCameras[mCameraFreeList.back()] = pCamera;
		mCameraEntityMap[pEntityID] = static_cast<unsigned short>(mCameraFreeList.back());
		mCameraFreeList.pop_back();
	}

	//Adjust mask then assign entity
	entity->componentMask |= ComponentType::COMPONENT_CAMERA;
	AssignEntity(*entity);
}

/// <summary>
/// Adds a Collision component to the entity with a given ID
/// </summary>
/// <param name="pCollision">Collision component to add</param>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::AddCollisionComp(const Collision & pCollision, const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	if (mCollisionFreeList.empty())
	{
		//Push onto back if no free slots and map to back
		mCollisions.push_back(pCollision);
		mCollisionEntityMap[pEntityID] = static_cast<unsigned short>(mCollisions.size() - 1);
	}
	else
	{
		//Insert into free slot and map to free slot
		mCollisions[mCollisionFreeList.back()] = pCollision;
		mCollisionEntityMap[pEntityID] = static_cast<unsigned short>(mCollisionFreeList.back());
		mCollisionFreeList.pop_back();
	}

	//Adjust mask then assign entity
	entity->componentMask |= ComponentType::COMPONENT_COLLISION;
	AssignEntity(*entity);
}

/// <summary>
/// Adds a Colour component to the entity with a given ID
/// </summary>
/// <param name="pColour">Colour component to add</param>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::AddColourComp(const Colour & pColour, const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	if (mColourFreeList.empty())
	{
		//Push onto back if no free slots and map to back
		mColours.push_back(pColour);
		mColourEntityMap[pEntityID] = static_cast<unsigned short>(mColours.size() - 1);
	}
	else
	{
		//Insert into free slot and map to free slot
		mColours[mColourFreeList.back()] = pColour;
		mColourEntityMap[pEntityID] = static_cast<unsigned short>(mColourFreeList.back());
		mColourFreeList.pop_back();
	}

	//Adjust mask then assign entity
	entity->componentMask |= ComponentType::COMPONENT_COLOUR;
	AssignEntity(*entity);
}

/// <summary>
/// Adds a Geometry component to the entity with a given ID
/// </summary>
/// <param name="pGeometry">Geometry component to add</param>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::AddGeometryComp(const Geometry & pGeometry, const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	if (mGeometryFreeList.empty())
	{
		//Push onto back if no free slots and map to back
		mGeometries.push_back(pGeometry);
		mGeometryEntityMap[pEntityID] = static_cast<unsigned short>(mGeometries.size() - 1);
	}
	else
	{
		//Insert into free slot and map to free slot
		mGeometries[mGeometryFreeList.back()] = pGeometry;
		mGeometryEntityMap[pEntityID] = static_cast<unsigned short>(mGeometryFreeList.back());
		mGeometryFreeList.pop_back();
	}

	//Adjust mask then assign entity
	entity->componentMask |= ComponentType::COMPONENT_GEOMETRY;
	AssignEntity(*entity);
}

/// <summary>
/// Adds a Gravity component to the entity with a given ID
/// </summary>
/// <param name="pGravity">Gravity component to add</param>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::AddGravityComp(const Gravity & pGravity, const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	if (mGravityFreeList.empty())
	{
		//Push onto back if no free slots and map to back
		mGravities.push_back(pGravity);
		mGravityEntityMap[pEntityID] = static_cast<unsigned short>(mGravities.size() - 1);
	}
	else
	{
		//Insert into free slot and map to free slot
		mGravities[mGravityFreeList.back()] = pGravity;
		mGravityEntityMap[pEntityID] = static_cast<unsigned short>(mGravityFreeList.back());
		mGravityFreeList.pop_back();
	}

	//Adjust mask then assign entity
	entity->componentMask |= ComponentType::COMPONENT_GRAVITY;
	AssignEntity(*entity);
}

/// <summary>
/// Adds a Point Light component to the entity with a given ID
/// </summary>
/// <param name="pLight">Light component to add</param>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::AddPointLightComp(const PointLight & pLight, const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	if (mPointLightFreeList.empty())
	{
		//Push onto back if no free slots and map to back
		mPointLights.push_back(pLight);
		mPointLightEntityMap[pEntityID] = static_cast<unsigned short>(mPointLights.size() - 1);
	}
	else
	{
		//Insert into free slot and map to free slot
		mPointLights[mPointLightFreeList.back()] = pLight;
		mPointLightEntityMap[pEntityID] = static_cast<unsigned short>(mPointLightFreeList.back());
		mPointLightFreeList.pop_back();
	}

	//Adjust mask then assign entity
	entity->componentMask |= ComponentType::COMPONENT_POINTLIGHT;
	AssignEntity(*entity);
}

/// <summary>
/// Adds a Directional Light component to the entity with a given ID
/// </summary>
/// <param name="pLight">Light component to add</param>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::AddDirectionalLightComp(const DirectionalLight & pLight, const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	if (mDirectionalLightFreeList.empty())
	{
		//Push onto back if no free slots and map to back
		mDirectionalLights.push_back(pLight);
		mDirectionalLightEntityMap[pEntityID] = static_cast<unsigned short>(mDirectionalLights.size() - 1);
	}
	else
	{
		//Insert into free slot and map to free slot
		mDirectionalLights[mDirectionalLightFreeList.back()] = pLight;
		mDirectionalLightEntityMap[pEntityID] = static_cast<unsigned short>(mDirectionalLightFreeList.back());
		mDirectionalLightFreeList.pop_back();
	}

	//Adjust mask then assign entity
	entity->componentMask |= ComponentType::COMPONENT_DIRECTIONALLIGHT;
	AssignEntity(*entity);
}

/// <summary>
/// Adds a Ray component to the entity with a given ID
/// </summary>
/// <param name="pRay">Ray component to add</param>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::AddRayComp(const Ray & pRay, const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	if (mRayFreeList.empty())
	{
		//Push onto back if no free slots and map to back
		mRays.push_back(pRay);
		mRayEntityMap[pEntityID] = static_cast<unsigned short>(mRays.size() - 1);
	}
	else
	{
		//Insert into free slot and map to free slot
		mRays[mRayFreeList.back()] = pRay;
		mRayEntityMap[pEntityID] = static_cast<unsigned short>(mRayFreeList.back());
		mRayFreeList.pop_back();
	}

	//Adjust mask then assign entity
	entity->componentMask |= ComponentType::COMPONENT_RAY;
	AssignEntity(*entity);
}

/// <summary>
/// Adds a Shader component to the entity with a given ID
/// </summary>
/// <param name="pShader">Shader component to add</param>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::AddShaderComp(const Shader & pShader, const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	if (mShaderFreeList.empty())
	{
		//Push onto back if no free slots and map to back
		mShaders.push_back(pShader);
		mShaderEntityMap[pEntityID] = static_cast<unsigned short>(mShaders.size() - 1);
	}
	else
	{
		//Insert into free slot and map to free slot
		mShaders[mShaderFreeList.back()] = pShader;
		mShaderEntityMap[pEntityID] = static_cast<unsigned short>(mShaderFreeList.back());
		mShaderFreeList.pop_back();
	}

	//Adjust mask then assign entity
	entity->componentMask |= ComponentType::COMPONENT_SHADER;
	AssignEntity(*entity);
}

/// <summary>
/// Adds a Sphere Collider component to the entity with a given ID
/// </summary>
/// <param name="pSphereCollider">Sphere Collider component to add</param>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::AddSphereColliderComp(const SphereCollider & pSphereCollider, const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	if (mSphereColliderFreeList.empty())
	{
		//Push onto back if no free slots and map to back
		mSphereColliders.push_back(pSphereCollider);
		mSphereColliderEntityMap[pEntityID] = static_cast<unsigned short>(mSphereColliders.size() - 1);
	}
	else
	{
		//Insert into free slot and map to free slot
		mSphereColliders[mSphereColliderFreeList.back()] = pSphereCollider;
		mSphereColliderEntityMap[pEntityID] = static_cast<unsigned short>(mSphereColliderFreeList.back());
		mSphereColliderFreeList.pop_back();
	}

	//Adjust mask then assign entity
	entity->componentMask |= ComponentType::COMPONENT_SPHERECOLLIDER;
	AssignEntity(*entity);
}

/// <summary>
/// Adds a Texture component to the entity with a given ID
/// </summary>
/// <param name="pTexture">Texture component to add</param>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::AddTextureComp(const Texture & pTexture, const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	if (mTextureFreeList.empty())
	{
		//Push onto back if no free slots and map to back
		mTextures.push_back(pTexture);
		mTextureEntityMap[pEntityID] = static_cast<unsigned short>(mTextures.size() - 1);
	}
	else
	{
		//Insert into free slot and map to free slot
		mTextures[mTextureFreeList.back()] = pTexture;
		mTextureEntityMap[pEntityID] = static_cast<unsigned short>(mTextureFreeList.back());
		mTextureFreeList.pop_back();
	}

	//Adjust mask then assign entity
	entity->componentMask |= ComponentType::COMPONENT_TEXTURE;
	AssignEntity(*entity);
}

/// <summary>
/// Adds a Transform component to the entity with a given ID
/// </summary>
/// <param name="pTransform">Transform component to add</param>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::AddTransformComp(const Transform & pTransform, const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	if (mTransformFreeList.empty())
	{
		//Push onto back if no free slots and map to back
		mTransforms.push_back(pTransform);
		mTransformEntityMap[pEntityID] = static_cast<unsigned short>(mTransforms.size() - 1);
	}
	else
	{
		//Insert into free slot and map to free slot
		mTransforms[mTransformFreeList.back()] = pTransform;
		mTransformEntityMap[pEntityID] = static_cast<unsigned short>(mTransformFreeList.back());
		mTransformFreeList.pop_back();
	}

	//Adjust mask then assign entity
	entity->componentMask |= ComponentType::COMPONENT_TRANSFORM;
	AssignEntity(*entity);
}

/// <summary>
/// Adds a Velocity component to the entity with a given ID
/// </summary>
/// <param name="pVelocity">Velocity component to add</param>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::AddVelocityComp(const Velocity & pVelocity, const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	if (mVelocityFreeList.empty())
	{
		//Push onto back if no free slots and map to back
		mVelocities.push_back(pVelocity);
		mVelocityEntityMap[pEntityID] = static_cast<unsigned short>(mVelocities.size() - 1);
	}
	else
	{
		//Insert into free slot and map to free slot
		mVelocities[mVelocityFreeList.back()] = pVelocity;
		mVelocityEntityMap[pEntityID] = static_cast<unsigned short>(mVelocityFreeList.back());
		mVelocityFreeList.pop_back();
	}

	//Adjust mask then assign entity
	entity->componentMask |= ComponentType::COMPONENT_VELOCITY;
	AssignEntity(*entity);
}

/// <summary>
/// Removes an AI component from the entity with a given ID
/// </summary>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::RemoveAIComp(const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	//Checks if entity actually owns a component of this type
	if ((entity->componentMask & ComponentType::COMPONENT_AI) == ComponentType::COMPONENT_AI)
	{
		//Add slot in ai array to free list
		mAIFreeList.push_back(mAIEntityMap[pEntityID]);

		//Update mask and reassign entity
		entity->componentMask = entity->componentMask &= ~ComponentType::COMPONENT_AI; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
		ReAssignEntity(*entity);
	}
}

/// <summary>
/// Removes an Audio component from the entity with a given ID
/// </summary>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::RemoveAudioComp(const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	//Checks if entity actually owns a component of this type
	if ((entity->componentMask & ComponentType::COMPONENT_AUDIO) == ComponentType::COMPONENT_AUDIO)
	{
		//Add slot in audio array to free list
		mAudioFreeList.push_back(mAudioEntityMap[pEntityID]);

		//Update mask and reassign entity
		entity->componentMask = entity->componentMask &= ~ComponentType::COMPONENT_AUDIO; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
		ReAssignEntity(*entity);
	}
}

/// <summary>
/// Removes a BoxCollider component from the entity with a given ID
/// </summary>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::RemoveBoxColliderComp(const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	//Checks if entity actually owns a component of this type
	if ((entity->componentMask & ComponentType::COMPONENT_BOXCOLLIDER) == ComponentType::COMPONENT_BOXCOLLIDER)
	{
		//Add slot in box collider array to free list
		mBoxColliderFreeList.push_back(mBoxColliderEntityMap[pEntityID]);

		//Update mask and reassign entity
		entity->componentMask = entity->componentMask &= ~ComponentType::COMPONENT_BOXCOLLIDER; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
		ReAssignEntity(*entity);
	}
}


/// <summary>
/// Removes a Camera component from the entity with a given ID
/// </summary>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::RemoveCameraComp(const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	//Checks if entity actually owns a component of this type
	if ((entity->componentMask & ComponentType::COMPONENT_CAMERA) == ComponentType::COMPONENT_CAMERA)
	{
		//Add slot in camera array to free list
		mCameraFreeList.push_back(mCameraEntityMap[pEntityID]);

		//Update mask and reassign entity
		entity->componentMask = entity->componentMask &= ~ComponentType::COMPONENT_CAMERA; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
		ReAssignEntity(*entity);
	}
}

/// <summary>
/// Removes a Collision component from the entity with a given ID
/// </summary>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::RemoveCollisionComp(const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	//Checks if entity actually owns a component of this type
	if ((entity->componentMask & ComponentType::COMPONENT_COLLISION) == ComponentType::COMPONENT_COLLISION)
	{
		//Add slot in collision array to free list
		mCollisionFreeList.push_back(mCollisionEntityMap[pEntityID]);

		//Update mask and reassign entity
		entity->componentMask = entity->componentMask &= ~ComponentType::COMPONENT_COLLISION; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
		ReAssignEntity(*entity);
	}
}

/// <summary>
/// Removes a Colour component from the entity with a given ID
/// </summary>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::RemoveColourComp(const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	//Checks if entity actually owns a component of this type
	if ((entity->componentMask & ComponentType::COMPONENT_COLOUR) == ComponentType::COMPONENT_COLOUR)
	{
		//Add slot in colour array to free list
		mColourFreeList.push_back(mColourEntityMap[pEntityID]);

		//Update mask and reassign entity
		entity->componentMask = entity->componentMask &= ~ComponentType::COMPONENT_COLOUR; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
		ReAssignEntity(*entity);
	}
}


/// <summary>
/// Removes a Geometry component from the entity with a given ID
/// </summary>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::RemoveGeometryComp(const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	//Checks if entity actually owns a component of this type
	if ((entity->componentMask & ComponentType::COMPONENT_GEOMETRY) == ComponentType::COMPONENT_GEOMETRY)
	{
		//Add slot in geometry array to free list
		mGeometryFreeList.push_back(mGeometryEntityMap[pEntityID]);

		//Update mask and reassign entity
		entity->componentMask = entity->componentMask &= ~ComponentType::COMPONENT_GEOMETRY; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
		ReAssignEntity(*entity);
	}
}

/// <summary>
/// Removes a Gravity component from the entity with a given ID
/// </summary>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::RemoveGravityComp(const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	//Checks if entity actually owns a component of this type
	if ((entity->componentMask & ComponentType::COMPONENT_GRAVITY) == ComponentType::COMPONENT_GRAVITY)
	{
		//Add slot in gravity array to free list
		mGravityFreeList.push_back(mGravityEntityMap[pEntityID]);

		//Update mask and reassign entity
		entity->componentMask = entity->componentMask &= ~ComponentType::COMPONENT_GRAVITY; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
		ReAssignEntity(*entity);
	}
}


/// <summary>
/// Removes a Light component from the entity with a given ID
/// </summary>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::RemovePointLightComp(const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	//Checks if entity actually owns a component of this type
	if ((entity->componentMask & ComponentType::COMPONENT_POINTLIGHT) == ComponentType::COMPONENT_POINTLIGHT)
	{
		//Add slot in light array to free list
		mPointLightFreeList.push_back(mPointLightEntityMap[pEntityID]);

		//Update mask and reassign entity
		entity->componentMask = entity->componentMask &= ~ComponentType::COMPONENT_POINTLIGHT; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
		ReAssignEntity(*entity);
	}
}

void ECSManager::RemoveDirectionalLightComp(const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	//Checks if entity actually owns a component of this type
	if ((entity->componentMask & ComponentType::COMPONENT_DIRECTIONALLIGHT) == ComponentType::COMPONENT_DIRECTIONALLIGHT)
	{
		//Add slot in light array to free list
		mDirectionalLightFreeList.push_back(mDirectionalLightEntityMap[pEntityID]);

		//Update mask and reassign entity
		entity->componentMask = entity->componentMask &= ~ComponentType::COMPONENT_DIRECTIONALLIGHT; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
		ReAssignEntity(*entity);
	}
}

/// <summary>
/// Removes a Ray component from the entity with a given ID
/// </summary>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::RemoveRayComp(const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	//Checks if entity actually owns a component of this type
	if ((entity->componentMask & ComponentType::COMPONENT_RAY) == ComponentType::COMPONENT_RAY)
	{
		//Add slot in ray array to free list
		mRayFreeList.push_back(mRayEntityMap[pEntityID]);

		//Update mask and reassign entity
		entity->componentMask = entity->componentMask &= ~ComponentType::COMPONENT_RAY; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
		ReAssignEntity(*entity);
	}
}


/// <summary>
/// Removes a Shader component from the entity with a given ID
/// </summary>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::RemoveShaderComp(const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	//Checks if entity actually owns a component of this type
	if ((entity->componentMask & ComponentType::COMPONENT_SHADER) == ComponentType::COMPONENT_SHADER)
	{
		//Add slot in shader array to free list
		mShaderFreeList.push_back(mShaderEntityMap[pEntityID]);

		//Update mask and reassign entity
		entity->componentMask = entity->componentMask &= ~ComponentType::COMPONENT_SHADER; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
		ReAssignEntity(*entity);
	}
}

/// <summary>
/// Removes a Sphere Collider component from the entity with a given ID
/// </summary>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::RemoveSphereColliderComp(const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	//Checks if entity actually owns a component of this type
	if ((entity->componentMask & ComponentType::COMPONENT_SPHERECOLLIDER) == ComponentType::COMPONENT_SPHERECOLLIDER)
	{
		//Add slot in sphere collider array to free list
		mSphereColliderFreeList.push_back(mSphereColliderEntityMap[pEntityID]);

		//Update mask and reassign entity
		entity->componentMask = entity->componentMask &= ~ComponentType::COMPONENT_SPHERECOLLIDER; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
		ReAssignEntity(*entity);
	}
}

/// <summary>
/// Removes a Texture component from the entity with a given ID
/// </summary>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::RemoveTextureComp(const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	//Checks if entity actually owns a component of this type
	if ((entity->componentMask & ComponentType::COMPONENT_TEXTURE) == ComponentType::COMPONENT_TEXTURE)
	{
		//Add slot in texture array to free list
		mTextureFreeList.push_back(mTextureEntityMap[pEntityID]);

		//Update mask and reassign entity
		entity->componentMask = entity->componentMask &= ~ComponentType::COMPONENT_TEXTURE; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
		ReAssignEntity(*entity);
	}
}


/// <summary>
/// Removes a Transform component from the entity with a given ID
/// </summary>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::RemoveTransformComp(const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	//Checks if entity actually owns a component of this type
	if ((entity->componentMask & ComponentType::COMPONENT_TRANSFORM) == ComponentType::COMPONENT_TRANSFORM)
	{
		//Add slot in transform array to free list
		mTransformFreeList.push_back(mTransformEntityMap[pEntityID]);

		//Update mask and reassign entity
		entity->componentMask = entity->componentMask &= ~ComponentType::COMPONENT_TRANSFORM; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
		ReAssignEntity(*entity);
	}
}

/// <summary>
/// Removes a Velocity component from the entity with a given ID
/// </summary>
/// <param name="pEntityID">Given ID of the entity</param>
void ECSManager::RemoveVelocityComp(const int pEntityID)
{
	Entity* entity = &mEntities[pEntityID];

	//Checks if entity actually owns a component of this type
	if ((entity->componentMask & ComponentType::COMPONENT_VELOCITY) == ComponentType::COMPONENT_VELOCITY)
	{
		//Add slot in velocity array to free list
		mVelocityFreeList.push_back(mVelocityEntityMap[pEntityID]);

		//Update mask and reassign entity
		entity->componentMask = entity->componentMask &= ~ComponentType::COMPONENT_VELOCITY; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
		ReAssignEntity(*entity);
	}
}

/// <summary>
/// Returns a modifiable handle to the AI component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to AI component</returns>
AI * const ECSManager::AIComp(const int pEntityID)
{
	//Checks if entity actually owns a component of this type
	if ((mEntities[pEntityID].componentMask & ComponentType::COMPONENT_AI) == ComponentType::COMPONENT_AI)
	{
		return &mAIs[mAIEntityMap[pEntityID]];
	}
	return nullptr;
}

/// <summary>
/// Returns a modifiable handle to the Audio component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to Audio component</returns>
Audio * const ECSManager::AudioComp(const int pEntityID)
{
	//Checks if entity actually owns a component of this type
	if ((mEntities[pEntityID].componentMask & ComponentType::COMPONENT_AUDIO) == ComponentType::COMPONENT_AUDIO)
	{
		return &mAudios[mAudioEntityMap[pEntityID]];
	}
	return nullptr;
}

/// <summary>
/// Returns a modifiable handle to the BoxCollider component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to BoxCollider component</returns>
BoxCollider * const ECSManager::BoxColliderComp(const int pEntityID)
{
	//Checks if entity actually owns a component of this type
	if ((mEntities[pEntityID].componentMask & ComponentType::COMPONENT_BOXCOLLIDER) == ComponentType::COMPONENT_BOXCOLLIDER)
	{
		return &mBoxColliders[mBoxColliderEntityMap[pEntityID]];
	}
	return nullptr;
}

/// <summary>
/// Returns a modifiable handle to the Camera component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to Camera component</returns>
Camera * const ECSManager::CameraComp(const int pEntityID)
{
	//Checks if entity actually owns a component of this type
	if ((mEntities[pEntityID].componentMask & ComponentType::COMPONENT_CAMERA) == ComponentType::COMPONENT_CAMERA)
	{
		return &mCameras[mCameraEntityMap[pEntityID]];
	}
	return nullptr;
}

/// <summary>
/// Returns a modifiable handle to the Collision component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to Collision component</returns>
Collision * const ECSManager::CollisionComp(const int pEntityID)
{
	//Checks if entity actually owns a component of this type
	if ((mEntities[pEntityID].componentMask & ComponentType::COMPONENT_COLLISION) == ComponentType::COMPONENT_COLLISION)
	{
		return &mCollisions[mCollisionEntityMap[pEntityID]];
	}
	return nullptr;
}

/// <summary>
/// Returns a modifiable handle to the Colour component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to Colour component</returns>
Colour * const ECSManager::ColourComp(const int pEntityID)
{
	//Checks if entity actually owns a component of this type
	if ((mEntities[pEntityID].componentMask & ComponentType::COMPONENT_COLOUR) == ComponentType::COMPONENT_COLOUR)
	{
		return &mColours[mColourEntityMap[pEntityID]];
	}
	return nullptr;
}

/// <summary>
/// Returns a modifiable handle to the Geometry component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to Geometry component</returns>
Geometry * const ECSManager::GeometryComp(const int pEntityID)
{
	//Checks if entity actually owns a component of this type
	if ((mEntities[pEntityID].componentMask & ComponentType::COMPONENT_GEOMETRY) == ComponentType::COMPONENT_GEOMETRY)
	{
		return &mGeometries[mGeometryEntityMap[pEntityID]];
	}
	return nullptr;
}

/// <summary>
/// Returns a modifiable handle to the Gravity component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to Geometry component</returns>
Gravity * const ECSManager::GravityComp(const int pEntityID)
{
	//Checks if entity actually owns a component of this type
	if ((mEntities[pEntityID].componentMask & ComponentType::COMPONENT_GRAVITY) == ComponentType::COMPONENT_GRAVITY)
	{
		return &mGravities[mGravityEntityMap[pEntityID]];
	}
	return nullptr;
}

/// <summary>
/// Returns a modifiable handle to the Light component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to AI component</returns>
PointLight * const ECSManager::PointLightComp(const int pEntityID)
{
	//Checks if entity actually owns a component of this type
	if ((mEntities[pEntityID].componentMask & ComponentType::COMPONENT_POINTLIGHT) == ComponentType::COMPONENT_POINTLIGHT)
	{
		return &mPointLights[mPointLightEntityMap[pEntityID]];
	}
	return nullptr;
}

DirectionalLight * const ECSManager::DirectionalLightComp(const int pEntityID)
{
	//Checks if entity actually owns a component of this type
	if ((mEntities[pEntityID].componentMask & ComponentType::COMPONENT_DIRECTIONALLIGHT) == ComponentType::COMPONENT_DIRECTIONALLIGHT)
	{
		return &mDirectionalLights[mDirectionalLightEntityMap[pEntityID]];
	}
	return nullptr;
}

/// <summary>
/// Returns a modifiable handle to the Ray component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to Ray component</returns>
Ray * const ECSManager::RayComp(const int pEntityID)
{
	//Checks if entity actually owns a component of this type
	if ((mEntities[pEntityID].componentMask & ComponentType::COMPONENT_RAY) == ComponentType::COMPONENT_RAY)
	{
		return &mRays[mRayEntityMap[pEntityID]];
	}
	return nullptr;
}

/// <summary>
/// Returns a modifiable handle to the Shader component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to Shader component</returns>
Shader * const ECSManager::ShaderComp(const int pEntityID)
{
	//Checks if entity actually owns a component of this type
	if ((mEntities[pEntityID].componentMask & ComponentType::COMPONENT_SHADER) == ComponentType::COMPONENT_SHADER)
	{
		return &mShaders[mShaderEntityMap[pEntityID]];
	}
	return nullptr;
}

/// <summary>
/// Returns a modifiable handle to the Sphere Collider component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to Sphere Collider component</returns>
SphereCollider * const ECSManager::SphereColliderComp(const int pEntityID)
{
	//Checks if entity actually owns a component of this type
	if ((mEntities[pEntityID].componentMask & ComponentType::COMPONENT_SPHERECOLLIDER) == ComponentType::COMPONENT_SPHERECOLLIDER)
	{
		return &mSphereColliders[mSphereColliderEntityMap[pEntityID]];
	}
	return nullptr;
}

/// <summary>
/// Returns a modifiable handle to the Texture component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to Texture component</returns>
Texture * const ECSManager::TextureComp(const int pEntityID)
{
	//Checks if entity actually owns a component of this type
	if ((mEntities[pEntityID].componentMask & ComponentType::COMPONENT_TEXTURE) == ComponentType::COMPONENT_TEXTURE)
	{
		return &mTextures[mTextureEntityMap[pEntityID]];
	}
	return nullptr;
}

/// <summary>
/// Returns a modifiable handle to the Transform component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to Transform component</returns>
Transform * const ECSManager::TransformComp(const int pEntityID)
{
	//Checks if entity actually owns a component of this type
	if ((mEntities[pEntityID].componentMask & ComponentType::COMPONENT_TRANSFORM) == ComponentType::COMPONENT_TRANSFORM)
	{
		return &mTransforms[mTransformEntityMap[pEntityID]];
	}
	return nullptr;
}

/// <summary>
/// Returns a modifiable handle to the Velocity component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to Velocity component</returns>
Velocity * const ECSManager::VelocityComp(const int pEntityID)
{
	//Checks if entity actually owns a component of this type
	if ((mEntities[pEntityID].componentMask & ComponentType::COMPONENT_VELOCITY) == ComponentType::COMPONENT_VELOCITY)
	{
		return &mVelocities[mVelocityEntityMap[pEntityID]];
	}
	return nullptr;
}
