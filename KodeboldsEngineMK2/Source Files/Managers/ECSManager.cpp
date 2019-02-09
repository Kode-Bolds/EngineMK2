#include "ECSManager.h"

using namespace std;

/// <summary>
/// Assigns given entity to all appropriate systems
/// </summary>
/// <param name="pEntity">The given entity to assign to systems</param>
void ECSManager::AssignEntity(const Entity & pEntity)
{
	for (auto & system : mRenderSystems)
	{
		system->AssignEntity(pEntity.mID);
	}

	for (auto & system : mUpdateSystems)
	{
		system->AssignEntity(pEntity.mID);
	}
}

/// <summary>
/// Removes given entity from all appropriate systems
/// </summary>
/// <param name="pEntity">The given entity to remove from systems</param>
void ECSManager::RemoveEntity(const Entity & pEntity)
{
	for (auto & system : mRenderSystems)
	{
		system->RemoveEntity(pEntity.mID);
	}

	for (auto & system : mUpdateSystems)
	{
		system->RemoveEntity(pEntity.mID);
	}
}

/// <summary>
/// Finds an entities ID based on a given name
/// </summary>
/// <param name="pEntityName">Given name of the entity</param>
/// <returns>ID of the entity</returns>
const int& ECSManager::FindEntityID(const std::string & pEntityName) const
{
	//Finds if an entity with this name already exists and returns an iterator to the entity if it does otherwise returns an iterator pointing to the end of the vector
	auto entity = find_if(mEntities.begin(), mEntities.end(), [&](const Entity& entity) {return entity.mName == pEntityName; });

	if (entity != mEntities.end())
	{
		return entity->mID;
	}
	else
	{
		return -1;
	}
}

/// <summary>
/// Constructor for ECS Manager
/// Resizes entity and component vectors upon construction to a reasonably large size to avoid performance overhead of resizing
/// </summary>
ECSManager::ECSManager()
{
		mEntities.resize(1000);
		mTransforms.resize(1000);
		mVelocities.resize(1000);
		mBoxColliders.resize(1000);
		mSphereColliders.resize(1000);
		mGeometries.resize(1000);
		mTextures.resize(1000);
		mShaders.resize(1000);
		mCameras.resize(1000);
		mLights.resize(1000);
		mGravities.resize(1000);
		mAudios.resize(1000);
		mAIs.resize(1000);
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
/// Creates an entity with the given name
/// Appends (nameCount) to the end of the entity name if entity name is duplicate
/// </summary>
/// <param name="pEntityName">Given name of the entity to create</param>
void ECSManager::CreateEntity(const std::string & pEntityName)
{
	Entity newEntity;

	//Finds if a pair with this name already exists and returns an iterator to the <name, count> pair value if it does otherwise returns an iterator pointing to the end of the vector
	auto entityName = find_if(mEntityNames.begin(), mEntityNames.end(), [&](const pair<string, int>& pair) {return pair.first == pEntityName; });

	//If the iterator is not pointing to the end of the vector, appends (nameCount) to the end of the given name and creates a new entity with that name, then iterates the name count by 1
	if (entityName != mEntityNames.end())
	{
		newEntity = Entity{ pEntityName + "(" + to_string(entityName->second) + ")", static_cast<int>(mEntities.size()), COMPONENT_NONE };
		mEntities.push_back(newEntity);
		entityName->second++;
	}
	//Else creates entity with given name and adds name to name vector with count 1
	else
	{
		newEntity = Entity{ pEntityName, static_cast<int>(mEntities.size()), COMPONENT_NONE };
		mEntities.push_back(newEntity);
		mEntityNames.push_back(std::pair<string, int>(pEntityName, 1));
	}
}

/// <summary>
/// Destroys an entity with the given name
/// </summary>
/// <param name="pEntityName">Given name of the entity to delete</param>
void ECSManager::DestroyEntity(const std::string & pEntityName)
{
	//Finds the entity with the matching name and removes it from the entities vector
	mEntities.erase(remove_if(mEntities.begin(), mEntities.end(), [&](const Entity& entity) {return entity.mName == pEntityName; }));
}

/// <summary>
/// Adds the given component of the given type to the given entity
/// </summary>
/// <param name="pComponentType">Given type of the component to add</param>
/// <param name="pComponent">Pointer to the given component to add</param>
/// <param name="pEntityName">Given name of the entity to add the component to</param>
void ECSManager::AddComponent(const ComponentType& pComponentType, const std::shared_ptr<const IComponent> pComponent, const std::string & pEntityName)
{
	int entityID = FindEntityID(pEntityName);

	//If entityID is found, adds the new component to the component vector of the appropriate type and modifies the entities component mask appropriately
	//Then assigns entity to systems that may be interested in that entity with the addition of the new component
	if (entityID != -1)
	{
		switch (pComponentType)
		{
		case COMPONENT_TRANSFORM:
			mTransforms.push_back(pair<int, Transform>(entityID, *dynamic_pointer_cast<const Transform>(pComponent)));
			mEntities[entityID].mComponentMask |= COMPONENT_TRANSFORM;
			AssignEntity(mEntities[entityID]);
			break;
		case COMPONENT_VELOCITY:
			mVelocities.push_back(pair<int, Velocity>(entityID, *dynamic_pointer_cast<const Velocity>(pComponent)));
			mEntities[entityID].mComponentMask |= COMPONENT_VELOCITY;
			AssignEntity(mEntities[entityID]);
			break;
		case COMPONENT_BOXCOLLIDER:
			mBoxColliders.push_back(pair<int, BoxCollider>(entityID, *dynamic_pointer_cast<const BoxCollider>(pComponent)));
			mEntities[entityID].mComponentMask |= COMPONENT_BOXCOLLIDER;
			AssignEntity(mEntities[entityID]);
			break;
		case COMPONENT_SPHERECOLLIDER:
			mSphereColliders.push_back(pair<int, SphereCollider>(entityID, *dynamic_pointer_cast<const SphereCollider>(pComponent)));
			mEntities[entityID].mComponentMask |= COMPONENT_SPHERECOLLIDER;
			AssignEntity(mEntities[entityID]);
			break;
		case COMPONENT_GEOMETRY:
			mGeometries.push_back(pair<int, Geometry>(entityID, *dynamic_pointer_cast<const Geometry>(pComponent)));
			mEntities[entityID].mComponentMask |= COMPONENT_GEOMETRY;
			AssignEntity(mEntities[entityID]);
			break;
		case COMPONENT_TEXTURE:
			mTextures.push_back(pair<int, Texture>(entityID, *dynamic_pointer_cast<const Texture>(pComponent)));
			mEntities[entityID].mComponentMask |= COMPONENT_TEXTURE;
			AssignEntity(mEntities[entityID]);
			break;
		case COMPONENT_SHADER:
			mShaders.push_back(pair<int, Shader>(entityID, *dynamic_pointer_cast<const Shader>(pComponent)));
			mEntities[entityID].mComponentMask |= COMPONENT_SHADER;
			AssignEntity(mEntities[entityID]);
			break;
		case COMPONENT_CAMERA:
			mCameras.push_back(pair<int, Camera>(entityID, *dynamic_pointer_cast<const Camera>(pComponent)));
			mEntities[entityID].mComponentMask |= COMPONENT_CAMERA;
			AssignEntity(mEntities[entityID]);
			break;
		case COMPONENT_LIGHT:
			mLights.push_back(pair<int, Light>(entityID, *dynamic_pointer_cast<const Light>(pComponent)));
			mEntities[entityID].mComponentMask |= COMPONENT_LIGHT;
			AssignEntity(mEntities[entityID]);
			break;
		case COMPONENT_GRAVITY:
			mGravities.push_back(pair<int, Gravity>(entityID, *dynamic_pointer_cast<const Gravity>(pComponent)));
			mEntities[entityID].mComponentMask |= COMPONENT_GRAVITY;
			AssignEntity(mEntities[entityID]);
			break;
		case COMPONENT_AUDIO:
			mAudios.push_back(pair<int, Audio>(entityID, *dynamic_pointer_cast<const Audio>(pComponent)));
			mEntities[entityID].mComponentMask |= COMPONENT_AUDIO;
			AssignEntity(mEntities[entityID]);
			break;
		case COMPONENT_AI:
			mAIs.push_back(pair<int, AI>(entityID, *dynamic_pointer_cast<const AI>(pComponent)));
			mEntities[entityID].mComponentMask |= COMPONENT_AI;
			AssignEntity(mEntities[entityID]);
			break;
		}
	}
}

/// <summary>
/// Removes the component of the given type from the given entity
/// </summary>
/// <param name="pComponentType">Given type of the component to remove</param>
/// <param name="pEntityName">Given name entity to remove the component from</param>
void ECSManager::RemoveComponent(const ComponentType & pComponentType, const std::string & pEntityName)
{
	int entityID = FindEntityID(pEntityName);

	//If entityID is found, removes the component from the component vector of the appropriate type and modifies the entities component mask appropriately
	//Then checks if entity needs reassigning from systems that may no longer be interested in that entity with the removal of the component
	if (entityID != -1)
	{
		switch (pComponentType)
		{
		case COMPONENT_TRANSFORM:
			mTransforms.erase(remove_if(mTransforms.begin(), mTransforms.end(), [&](const pair<int, Transform>& pair) {return pair.first == entityID; }));
			//MODIFY MASK HERE "POSSIBLY |= AGAIN?"
			AssignEntity(mEntities[entityID]);
			break;
		case COMPONENT_VELOCITY:
			mVelocities.erase(remove_if(mVelocities.begin(), mVelocities.end(), [&](const pair<int, Velocity>& pair) {return pair.first == entityID; }));
			//MODIFY MASK HERE "POSSIBLY |= AGAIN?"
			AssignEntity(mEntities[entityID]);
			break;
		case COMPONENT_BOXCOLLIDER:
			mBoxColliders.erase(remove_if(mBoxColliders.begin(), mBoxColliders.end(), [&](const pair<int, BoxCollider>& pair) {return pair.first == entityID; }));
			//MODIFY MASK HERE "POSSIBLY |= AGAIN?"
			AssignEntity(mEntities[entityID]);
			break;
		case COMPONENT_SPHERECOLLIDER:
			mSphereColliders.erase(remove_if(mSphereColliders.begin(), mSphereColliders.end(), [&](const pair<int, SphereCollider>& pair) {return pair.first == entityID; }));
			//MODIFY MASK HERE "POSSIBLY |= AGAIN?"
			AssignEntity(mEntities[entityID]);
			break;
		case COMPONENT_GEOMETRY:
			mGeometries.erase(remove_if(mGeometries.begin(), mGeometries.end(), [&](const pair<int, Geometry>& pair) {return pair.first == entityID; }));
			//MODIFY MASK HERE "POSSIBLY |= AGAIN?"
			AssignEntity(mEntities[entityID]);
			break;
		case COMPONENT_TEXTURE:
			mTextures.erase(remove_if(mTextures.begin(), mTextures.end(), [&](const pair<int, Texture>& pair) {return pair.first == entityID; }));
			//MODIFY MASK HERE "POSSIBLY |= AGAIN?"
			AssignEntity(mEntities[entityID]);
			break;
		case COMPONENT_SHADER:
			mShaders.erase(remove_if(mShaders.begin(), mShaders.end(), [&](const pair<int, Shader>& pair) {return pair.first == entityID; }));
			//MODIFY MASK HERE "POSSIBLY |= AGAIN?"
			AssignEntity(mEntities[entityID]);
			break;
		case COMPONENT_CAMERA:
			mCameras.erase(remove_if(mCameras.begin(), mCameras.end(), [&](const pair<int, Camera>& pair) {return pair.first == entityID; }));
			//MODIFY MASK HERE "POSSIBLY |= AGAIN?"
			AssignEntity(mEntities[entityID]);
			break;
		case COMPONENT_LIGHT:
			mLights.erase(remove_if(mLights.begin(), mLights.end(), [&](const pair<int, Light>& pair) {return pair.first == entityID; }));
			//MODIFY MASK HERE "POSSIBLY |= AGAIN?"
			AssignEntity(mEntities[entityID]);
			break;
		case COMPONENT_GRAVITY:
			mGravities.erase(remove_if(mGravities.begin(), mGravities.end(), [&](const pair<int, Gravity>& pair) {return pair.first == entityID; }));
			//MODIFY MASK HERE "POSSIBLY |= AGAIN?"
			AssignEntity(mEntities[entityID]);
			break;
		case COMPONENT_AUDIO:
			mAudios.erase(remove_if(mAudios.begin(), mAudios.end(), [&](const pair<int, Audio>& pair) {return pair.first == entityID; }));
			//MODIFY MASK HERE "POSSIBLY |= AGAIN?"
			AssignEntity(mEntities[entityID]);
			break;
		case COMPONENT_AI:
			mAIs.erase(remove_if(mAIs.begin(), mAIs.end(), [&](const pair<int, AI>& pair) {return pair.first == entityID; }));
			//MODIFY MASK HERE "POSSIBLY |= AGAIN?"
			AssignEntity(mEntities[entityID]);
			break;
		}
	}
}

/// <summary>
/// Adds the given system to the update system vector
/// </summary>
/// <param name="pSystem">Pointer to the given system</param>
void ECSManager::AddUpdateSystem(const std::shared_ptr<ISystem> pSystem)
{
	mUpdateSystems.push_back(pSystem);
}

/// <summary>
/// Adds the given system to the render system vector
/// </summary>
/// <param name="pSystem">Pointer to the given system</param>
void ECSManager::AddRenderSystem(const std::shared_ptr<ISystem> pSystem)
{
	mRenderSystems.push_back(pSystem);
}

/// <summary>
/// Calls the process method for all systems in the ECS
/// </summary>
void ECSManager::ProcessSystems()
{
	for (auto & system : mUpdateSystems)
	{
		system->Process();
	}

	for (auto & system : mRenderSystems)
	{
		system->Process();
	}
}

/// <summary>
/// Returns a modifiable handle to the AI component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to AI component</returns>
AI & ECSManager::AIComp(const int & pEntityID)
{
	return mAIs[pEntityID].second;
}

/// <summary>
/// Returns a modifiable handle to the AI component associated with the given entity name
/// </summary>
/// <param name="pEntityName">Given entity name</param>
/// <returns>Modifiable handle to the AI component</returns>
AI & ECSManager::AIComp(const std::string & pEntityName)
{
	int entityID = FindEntityID(pEntityName);
	if (entityID != -1)
	{
		return mAIs[entityID].second;
	}
}

/// <summary>
/// Returns a modifiable handle to the Audio component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to Audio component</returns>
Audio & ECSManager::AudioComp(const int & pEntityID)
{
	return mAudios[pEntityID].second;
}

/// <summary>
/// Returns a modifiable handle to the Audio component associated with the given entity name
/// </summary>
/// <param name="pEntityName">Given entity name</param>
/// <returns>Modifiable handle to the Audio component</returns>
Audio & ECSManager::AudioComp(const std::string & pEntityName)
{
	int entityID = FindEntityID(pEntityName);
	if (entityID != -1)
	{
		return mAudios[entityID].second;
	}
}

/// <summary>
/// Returns a modifiable handle to the BoxCollider component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to BoxCollider component</returns>
BoxCollider & ECSManager::BoxColliderComp(const int & pEntityID)
{
	return mBoxColliders[pEntityID].second;
}

/// <summary>
/// Returns a modifiable handle to the BoxCollider component associated with the given entity name
/// </summary>
/// <param name="pEntityName">Given entity name</param>
/// <returns>Modifiable handle to the BoxCollider component</returns>
BoxCollider & ECSManager::BoxColliderComp(const std::string & pEntityName)
{
	int entityID = FindEntityID(pEntityName);
	if (entityID != -1)
	{
		return mBoxColliders[entityID].second;
	}
}

/// <summary>
/// Returns a modifiable handle to the Camera component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to Camera component</returns>
Camera & ECSManager::CameraComp(const int & pEntityID)
{
	return mCameras[pEntityID].second;
}

/// <summary>
/// Returns a modifiable handle to the Camera component associated with the given entity name
/// </summary>
/// <param name="pEntityName">Given entity name</param>
/// <returns>Modifiable handle to the Camera component</returns>
Camera & ECSManager::CameraComp(const std::string pEntityName)
{
	int entityID = FindEntityID(pEntityName);
	if (entityID != -1)
	{
		return mCameras[entityID].second;
	}
}

/// <summary>
/// Returns a modifiable handle to the Geometry component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to Geometry component</returns>
Geometry & ECSManager::GeometryComp(const int & pEntityID)
{
	return mGeometries[pEntityID].second;
}

/// <summary>
/// Returns a modifiable handle to the Geometry component associated with the given entity name
/// </summary>
/// <param name="pEntityName">Given entity name</param>
/// <returns>Modifiable handle to the Geometry component</returns>
Geometry & ECSManager::GeometryComp(const std::string & pEntityName)
{
	int entityID = FindEntityID(pEntityName);
	if (entityID != -1)
	{
		return mGeometries[entityID].second;
	}
}

/// <summary>
/// Returns a modifiable handle to the Gravity component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to Gravity component</returns>
Gravity & ECSManager::GravityComp(const int & pEntityID)
{
	return mGravities[pEntityID].second;
}

/// <summary>
/// Returns a modifiable handle to the Gravity component associated with the given entity name
/// </summary>
/// <param name="pEntityName">Given entity name</param>
/// <returns>Modifiable handle to the Gravity component</returns>
Gravity & ECSManager::GravityComp(const std::string & pEntityName)
{
	int entityID = FindEntityID(pEntityName);
	if (entityID != -1)
	{
		return mGravities[entityID].second;
	}
}

/// <summary>
/// Returns a modifiable handle to the Light component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to AI component</returns>
Light & ECSManager::LightComp(const int & pEntityID)
{
	return mLights[pEntityID].second;
}

/// <summary>
/// Returns a modifiable handle to the Light component associated with the given entity name
/// </summary>
/// <param name="pEntityName">Given entity name</param>
/// <returns>Modifiable handle to the Light component</returns>
Light & ECSManager::LightComp(const std::string & pEntityName)
{
	int entityID = FindEntityID(pEntityName);
	if (entityID != -1)
	{
		return mLights[entityID].second;
	}
}

/// <summary>
/// Returns a modifiable handle to the Shader component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to Shader component</returns>
Shader & ECSManager::ShaderComp(const int & pEntityID)
{
	return mShaders[pEntityID].second;
}

/// <summary>
/// Returns a modifiable handle to the Shader component associated with the given entity name
/// </summary>
/// <param name="pEntityName">Given entity name</param>
/// <returns>Modifiable handle to the Shader component</returns>
Shader & ECSManager::ShaderComp(const std::string & pEntityName)
{
	int entityID = FindEntityID(pEntityName);
	if (entityID != -1)
	{
		return mShaders[entityID].second;
	}
}

/// <summary>
/// Returns a modifiable handle to the SphereCollider component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to SphereCollider component</returns>
SphereCollider & ECSManager::SphereColliderComp(const int & pEntityID)
{
	return mSphereColliders[pEntityID].second;
}

/// <summary>
/// Returns a modifiable handle to the SphereCollider component associated with the given entity name
/// </summary>
/// <param name="pEntityName">Given entity name</param>
/// <returns>Modifiable handle to the SphereCollider component</returns>
SphereCollider & ECSManager::SphereColliderComp(const std::string & pEntityName)
{
	int entityID = FindEntityID(pEntityName);
	if (entityID != -1)
	{
		return mSphereColliders[entityID].second;
	}
}

/// <summary>
/// Returns a modifiable handle to the Texture component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to Texture component</returns>
Texture & ECSManager::TextureComp(const int & pEntityID)
{
	return mTextures[pEntityID].second;
}

/// <summary>
/// Returns a modifiable handle to the Texture component associated with the given entity name
/// </summary>
/// <param name="pEntityName">Given entity name</param>
/// <returns>Modifiable handle to the Texture component</returns>
Texture & ECSManager::TextureComp(const std::string & pEntityName)
{
	int entityID = FindEntityID(pEntityName);
	if (entityID != -1)
	{
		return mTextures[entityID].second;
	}
}

/// <summary>
/// Returns a modifiable handle to the Transform component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to Transform component</returns>
Transform & ECSManager::TransformComp(const int & pEntityID)
{
	return mTransforms[pEntityID].second;
}

/// <summary>
/// Returns a modifiable handle to the Transform component associated with the given entity name
/// </summary>
/// <param name="pEntityName">Given entity name</param>
/// <returns>Modifiable handle to the Transform component</returns>
Transform & ECSManager::TransformComp(const std::string & pEntityName)
{
	int entityID = FindEntityID(pEntityName);
	if (entityID != -1)
	{
		return mTransforms[entityID].second;
	}
}

/// <summary>
/// Returns a modifiable handle to the Velocity component associated with the given entity ID
/// </summary>
/// <param name="pEntityID">Given entity ID</param>
/// <returns>Modifiable handle to Velocity component</returns>
Velocity & ECSManager::VelocityComp(const int & pEntityID)
{
	return mVelocities[pEntityID].second;
}

/// <summary>
/// Returns a modifiable handle to the Velocity component associated with the given entity name
/// </summary>
/// <param name="pEntityName">Given entity name</param>
/// <returns>Modifiable handle to the Velocity component</returns>
Velocity & ECSManager::VelocityComp(const std::string & pEntityName)
{
	int entityID = FindEntityID(pEntityName);
	if (entityID != -1)
	{
		return mVelocities[entityID].second;
	}
}
