#include "..\..\Header Files\Managers\ECSManager.h"

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

	//Assigns new entity to appropriate systems
	AssignEntity(newEntity);
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
	//Finds if an entity with this name already exists and returns an iterator to the entity if it does otherwise returns an iterator pointing to the end of the vector
	auto entity = find_if(mEntities.begin(), mEntities.end(), [&](const Entity& entity) {return entity.mName == pEntityName; });

	//If the iterator is not pointing to the end of the vector, adds the new component to the component vector of the appropriate type and modifies the entities component mask appropriately
	if (entity != mEntities.end())
	{
		switch (pComponentType)
		{
		case COMPONENT_TRANSFORM:
			mTransforms.push_back(pair<int, Transform>(entity->mID, *dynamic_pointer_cast<const Transform>(pComponent)));
			entity->mComponentMask |= COMPONENT_TRANSFORM;
			break;
		case COMPONENT_VELOCITY:
			mVelocities.push_back(pair<int, Velocity>(entity->mID, *dynamic_pointer_cast<const Velocity>(pComponent)));
			entity->mComponentMask |= COMPONENT_VELOCITY;
			break;
		case COMPONENT_BOXCOLLIDER:
			mBoxColliders.push_back(pair<int, BoxCollider>(entity->mID, *dynamic_pointer_cast<const BoxCollider>(pComponent)));
			entity->mComponentMask |= COMPONENT_BOXCOLLIDER;
			break;
		case COMPONENT_SPHERECOLLIDER:
			mSphereColliders.push_back(pair<int, SphereCollider>(entity->mID, *dynamic_pointer_cast<const SphereCollider>(pComponent)));
			entity->mComponentMask |= COMPONENT_SPHERECOLLIDER;
			break;
		case COMPONENT_GEOMETRY:
			mGeometries.push_back(pair<int, Geometry>(entity->mID, *dynamic_pointer_cast<const Geometry>(pComponent)));
			entity->mComponentMask |= COMPONENT_GEOMETRY;
			break;
		case COMPONENT_TEXTURE:
			mTextures.push_back(pair<int, Texture>(entity->mID, *dynamic_pointer_cast<const Texture>(pComponent)));
			entity->mComponentMask |= COMPONENT_TEXTURE;
			break;
		case COMPONENT_SHADER:
			mShaders.push_back(pair<int, Shader>(entity->mID, *dynamic_pointer_cast<const Shader>(pComponent)));
			entity->mComponentMask |= COMPONENT_SHADER;
			break;
		case COMPONENT_CAMERA:
			mCameras.push_back(pair<int, Camera>(entity->mID, *dynamic_pointer_cast<const Camera>(pComponent)));
			entity->mComponentMask |= COMPONENT_CAMERA;
			break;
		case COMPONENT_LIGHT:
			mLights.push_back(pair<int, Light>(entity->mID, *dynamic_pointer_cast<const Light>(pComponent)));
			entity->mComponentMask |= COMPONENT_LIGHT;
			break;
		case COMPONENT_GRAVITY:
			mGravities.push_back(pair<int, Gravity>(entity->mID, *dynamic_pointer_cast<const Gravity>(pComponent)));
			entity->mComponentMask |= COMPONENT_GRAVITY;
			break;
		case COMPONENT_AUDIO:
			mAudios.push_back(pair<int, Audio>(entity->mID, *dynamic_pointer_cast<const Audio>(pComponent)));
			entity->mComponentMask |= COMPONENT_AUDIO;
			break;
		case COMPONENT_AI:
			mAIs.push_back(pair<int, AI>(entity->mID, *dynamic_pointer_cast<const AI>(pComponent)));
			entity->mComponentMask |= COMPONENT_AI;
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
	//Finds if an entity with this name already exists and returns an iterator to the entity if it does otherwise returns an iterator pointing to the end of the vector
	auto entity = find_if(mEntities.begin(), mEntities.end(), [&](const Entity& entity) {return entity.mName == pEntityName; });

	//If the iterator is not pointing to the end of the vector, removes the component from the component vector of the appropriate type and modifies the entities component mask appropriately
	if (entity != mEntities.end())
	{
		switch (pComponentType)
		{
		case COMPONENT_TRANSFORM:
			mTransforms.erase(remove_if(mTransforms.begin(), mTransforms.end(), [&](const pair<int, Transform>& pair) {return pair.first == entity->mID; }));
			break;
		case COMPONENT_VELOCITY:
			mVelocities.erase(remove_if(mVelocities.begin(), mVelocities.end(), [&](const pair<int, Velocity>& pair) {return pair.first == entity->mID; }));
			break;
		case COMPONENT_BOXCOLLIDER:
			mBoxColliders.erase(remove_if(mBoxColliders.begin(), mBoxColliders.end(), [&](const pair<int, BoxCollider>& pair) {return pair.first == entity->mID; }));
			break;
		case COMPONENT_SPHERECOLLIDER:
			mSphereColliders.erase(remove_if(mSphereColliders.begin(), mSphereColliders.end(), [&](const pair<int, SphereCollider>& pair) {return pair.first == entity->mID; }));
			break;
		case COMPONENT_GEOMETRY:
			mGeometries.erase(remove_if(mGeometries.begin(), mGeometries.end(), [&](const pair<int, Geometry>& pair) {return pair.first == entity->mID; }));
			break;
		case COMPONENT_TEXTURE:
			mTextures.erase(remove_if(mTextures.begin(), mTextures.end(), [&](const pair<int, Texture>& pair) {return pair.first == entity->mID; }));
			break;
		case COMPONENT_SHADER:
			mShaders.erase(remove_if(mShaders.begin(), mShaders.end(), [&](const pair<int, Shader>& pair) {return pair.first == entity->mID; }));
			break;
		case COMPONENT_CAMERA:
			mCameras.erase(remove_if(mCameras.begin(), mCameras.end(), [&](const pair<int, Camera>& pair) {return pair.first == entity->mID; }));
			break;
		case COMPONENT_LIGHT:
			mLights.erase(remove_if(mLights.begin(), mLights.end(), [&](const pair<int, Light>& pair) {return pair.first == entity->mID; }));
			break;
		case COMPONENT_GRAVITY:
			mGravities.erase(remove_if(mGravities.begin(), mGravities.end(), [&](const pair<int, Gravity>& pair) {return pair.first == entity->mID; }));
			break;
		case COMPONENT_AUDIO:
			mAudios.erase(remove_if(mAudios.begin(), mAudios.end(), [&](const pair<int, Audio>& pair) {return pair.first == entity->mID; }));
			break;
		case COMPONENT_AI:
			mAIs.erase(remove_if(mAIs.begin(), mAIs.end(), [&](const pair<int, AI>& pair) {return pair.first == entity->mID; }));
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
/// Gets a component of a given type for the entity of a given name
/// </summary>
/// <param name="pComponentType">Given type of the component to retrieve</param>
/// <param name="pEntityName">Given name of the entity that owns the component</param>
/// <returns></returns>
const std::shared_ptr<const IComponent> ECSManager::GetComponent(const ComponentType & pComponentType, const std::string & pEntityName) const
{
	//Finds if an entity with this name already exists and returns an iterator to the entity if it does otherwise returns an iterator pointing to the end of the vector
	auto entity = find_if(mEntities.begin(), mEntities.end(), [&](const Entity& entity) {return entity.mName == pEntityName; });

	//If the iterator is not pointing to the end of the vector, returns the corresponding component of the appropriate type
	if (entity != mEntities.end())
	{
		switch (pComponentType)
		{
		case COMPONENT_TRANSFORM: 
			return make_shared<const IComponent>(mTransforms[entity->mID].second);
			break;
		case COMPONENT_VELOCITY:
			return make_shared<const IComponent>(mVelocities[entity->mID].second);
			break;
		case COMPONENT_BOXCOLLIDER:
			return make_shared<const IComponent>(mBoxColliders[entity->mID].second);
			break;
		case COMPONENT_SPHERECOLLIDER:
			return make_shared<const IComponent>(mSphereColliders[entity->mID].second);
			break;
		case COMPONENT_GEOMETRY:
			return make_shared<const IComponent>(mGeometries[entity->mID].second);
			break;
		case COMPONENT_TEXTURE:
			return make_shared<const IComponent>(mTextures[entity->mID].second);
			break;
		case COMPONENT_SHADER:
			return make_shared<const IComponent>(mShaders[entity->mID].second);
			break;
		case COMPONENT_CAMERA:
			return make_shared<const IComponent>(mCameras[entity->mID].second);
			break;
		case COMPONENT_LIGHT:
			return make_shared<const IComponent>(mLights[entity->mID].second);
			break;
		case COMPONENT_GRAVITY:
			return make_shared<const IComponent>(mGravities[entity->mID].second);
			break;
		case COMPONENT_AUDIO:
			return make_shared<const IComponent>(mAudios[entity->mID].second);
			break;
		case COMPONENT_AI:
			return make_shared<const IComponent>(mAIs[entity->mID].second);
			break;
		}
	}

	return nullptr;
}

/// <summary>
/// Sets given type of component owned by given entity to the given instance of a component
/// </summary>
/// <param name="pComponentType">Given type of the component</param>
/// <param name="pComponent">Given instance of component</param>
/// <param name="pEntityName">Given name of the entity</param>
void ECSManager::SetComponent(const ComponentType & pComponentType, const std::shared_ptr<const IComponent> pComponent, const std::string pEntityName)
{
	//Finds if an entity with this name already exists and returns an iterator to the entity if it does otherwise returns an iterator pointing to the end of the vector
	auto entity = find_if(mEntities.begin(), mEntities.end(), [&](const Entity& entity) {return entity.mName == pEntityName; });

	//If the iterator is not pointing to the end of the vector, sets the given component type of the given entity to the given component instance
	if (entity != mEntities.end())
	{
		switch (pComponentType)
		{
		case COMPONENT_TRANSFORM:
			mTransforms[entity->mID].second = *dynamic_pointer_cast<const Transform>(pComponent);
			break;
		case COMPONENT_VELOCITY:
			mVelocities[entity->mID].second = *dynamic_pointer_cast<const Velocity>(pComponent);
			break;
		case COMPONENT_BOXCOLLIDER:
			mBoxColliders[entity->mID].second = *dynamic_pointer_cast<const BoxCollider>(pComponent);
			break;
		case COMPONENT_SPHERECOLLIDER:
			mSphereColliders[entity->mID].second = *dynamic_pointer_cast<const SphereCollider>(pComponent);
			break;
		case COMPONENT_GEOMETRY:
			mGeometries[entity->mID].second = *dynamic_pointer_cast<const Geometry>(pComponent);
			break;
		case COMPONENT_TEXTURE:
			mTextures[entity->mID].second = *dynamic_pointer_cast<const Texture>(pComponent);
			break;
		case COMPONENT_SHADER:
			mShaders[entity->mID].second = *dynamic_pointer_cast<const Shader>(pComponent);
			break;
		case COMPONENT_CAMERA:
			mCameras[entity->mID].second = *dynamic_pointer_cast<const Camera>(pComponent);
			break;
		case COMPONENT_LIGHT:
			mLights[entity->mID].second = *dynamic_pointer_cast<const Light>(pComponent);
			break;
		case COMPONENT_GRAVITY:
			mGravities[entity->mID].second = *dynamic_pointer_cast<const Gravity>(pComponent);
			break;
		case COMPONENT_AUDIO:
			mAudios[entity->mID].second = *dynamic_pointer_cast<const Audio>(pComponent);
			break;
		case COMPONENT_AI:
			mAIs[entity->mID].second = *dynamic_pointer_cast<const AI>(pComponent);
			break;
		}
	}
}

/// <summary>
/// Gets a component of a given type for the entity of a given ID
/// </summary>
/// <param name="pComponentType">Given type of the component to retrieve</param>
/// <param name="pEntityID">Given ID of the entity that owns the component</param>
/// <returns></returns>
const std::shared_ptr<const IComponent> ECSManager::GetComponent(const ComponentType & pComponentType, const int & pEntityID) const
{
	switch (pComponentType)
	{
	case COMPONENT_TRANSFORM:
		return make_shared<const IComponent>(mTransforms[pEntityID].second);
		break;
	case COMPONENT_VELOCITY:
		return make_shared<const IComponent>(mVelocities[pEntityID].second);
		break;
	case COMPONENT_BOXCOLLIDER:
		return make_shared<const IComponent>(mBoxColliders[pEntityID].second);
		break;
	case COMPONENT_SPHERECOLLIDER:
		return make_shared<const IComponent>(mSphereColliders[pEntityID].second);
		break;
	case COMPONENT_GEOMETRY:
		return make_shared<const IComponent>(mGeometries[pEntityID].second);
		break;
	case COMPONENT_TEXTURE:
		return make_shared<const IComponent>(mTextures[pEntityID].second);
		break;
	case COMPONENT_SHADER:
		return make_shared<const IComponent>(mShaders[pEntityID].second);
		break;
	case COMPONENT_CAMERA:
		return make_shared<const IComponent>(mCameras[pEntityID].second);
		break;
	case COMPONENT_LIGHT:
		return make_shared<const IComponent>(mLights[pEntityID].second);
		break;
	case COMPONENT_GRAVITY:
		return make_shared<const IComponent>(mGravities[pEntityID].second);
		break;
	case COMPONENT_AUDIO:
		return make_shared<const IComponent>(mAudios[pEntityID].second);
		break;
	case COMPONENT_AI:
		return make_shared<const IComponent>(mAIs[pEntityID].second);
		break;
	}

	return nullptr;
}

/// <summary>
/// Sets given type of component owned by given entity to the given instance of a component
/// </summary>
/// <param name="pComponentType">Given type of the component</param>
/// <param name="pComponent">Given instance of component</param>
/// <param name="pEntityName">Given ID of the entity</param>
void ECSManager::SetComponent(const ComponentType & pComponentType, const std::shared_ptr<const IComponent> pComponent, const int & pEntityID)
{
	switch (pComponentType)
	{
	case COMPONENT_TRANSFORM:
		mTransforms[pEntityID].second = *dynamic_pointer_cast<const Transform>(pComponent);
		break;
	case COMPONENT_VELOCITY:
		mVelocities[pEntityID].second = *dynamic_pointer_cast<const Velocity>(pComponent);
		break;
	case COMPONENT_BOXCOLLIDER:
		mBoxColliders[pEntityID].second = *dynamic_pointer_cast<const BoxCollider>(pComponent);
		break;
	case COMPONENT_SPHERECOLLIDER:
		mSphereColliders[pEntityID].second = *dynamic_pointer_cast<const SphereCollider>(pComponent);
		break;
	case COMPONENT_GEOMETRY:
		mGeometries[pEntityID].second = *dynamic_pointer_cast<const Geometry>(pComponent);
		break;
	case COMPONENT_TEXTURE:
		mTextures[pEntityID].second = *dynamic_pointer_cast<const Texture>(pComponent);
		break;
	case COMPONENT_SHADER:
		mShaders[pEntityID].second = *dynamic_pointer_cast<const Shader>(pComponent);
		break;
	case COMPONENT_CAMERA:
		mCameras[pEntityID].second = *dynamic_pointer_cast<const Camera>(pComponent);
		break;
	case COMPONENT_LIGHT:
		mLights[pEntityID].second = *dynamic_pointer_cast<const Light>(pComponent);
		break;
	case COMPONENT_GRAVITY:
		mGravities[pEntityID].second = *dynamic_pointer_cast<const Gravity>(pComponent);
		break;
	case COMPONENT_AUDIO:
		mAudios[pEntityID].second = *dynamic_pointer_cast<const Audio>(pComponent);
		break;
	case COMPONENT_AI:
		mAIs[pEntityID].second = *dynamic_pointer_cast<const AI>(pComponent);
		break;
	}
}
