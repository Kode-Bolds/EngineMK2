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
/// Ensures there is only ever one instance of ECS Manager using the Singleton pattern
/// Resizes entity and component vectors upon construction to a reasonably large size to avoid performance overhead of resizing
/// </summary>
ECSManager::ECSManager()
{
	if (!mInstance)
	{
		mInstance = make_shared<ECSManager>(this);

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
	else
	{
		delete this;
	}
}

/// <summary>
/// Default destructor
/// </summary>
ECSManager::~ECSManager()
{
}

/// <summary>
/// Returns a pointer to the instance of the ECS manager
/// </summary>
/// <returns></returns>
std::shared_ptr<ECSManager> ECSManager::Instance()
{
	return mInstance;
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
	auto it = find_if(mEntityNames.begin(), mEntityNames.end(), [&](const pair<string, int>& pair) {return pair.first == pEntityName; });

	//If the iterator is not pointing to the end of the vector, appends (nameCount) to the end of the given name and creates a new entity with that name, then iterates the name count by 1
	if (it != mEntityNames.end())
	{
		newEntity = Entity{ pEntityName + "(" + to_string(it->second) + ")", mEntities.size(), COMPONENT_NONE };
		mEntities.push_back(newEntity);
		it->second++;
	}
	//Else creates entity with given name and adds name to name vector with count 1
	else
	{
		newEntity = Entity{ pEntityName, mEntities.size(), COMPONENT_NONE };
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
	mEntities.erase(remove(mEntities.begin(), mEntities.end(), [&](const Entity& entity) {return entity.mName == pEntityName; }));
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
	auto it = find_if(mEntities.begin(), mEntities.end(), [&](const Entity& entity) {return entity.mName == pEntityName; });

	//If the iterator is not pointing to the end of the vector, adds the new component to the component vector of the appropriate type and modifies the entities component mask appropriately
	if (it != mEntities.end())
	{
		switch (pComponentType)
		{
		case COMPONENT_TRANSFORM:
			mTransforms.push_back(pair<int, Transform>(it->mID, *dynamic_pointer_cast<Transform>(pComponent)));
			it->mComponentMask |= COMPONENT_TRANSFORM;
			break;
		case COMPONENT_VELOCITY:
			mVelocities.push_back(pair<int, Velocity>(it->mID, *dynamic_pointer_cast<Velocity>(pComponent)));
			it->mComponentMask |= COMPONENT_VELOCITY;
			break;
		case COMPONENT_BOXCOLLIDER:
			mBoxColliders.push_back(pair<int, BoxCollider>(it->mID, *dynamic_pointer_cast<BoxCollider>(pComponent)));
			it->mComponentMask |= COMPONENT_BOXCOLLIDER;
			break;
		case COMPONENT_SPHERECOLLIDER:
			mSphereColliders.push_back(pair<int, SphereCollider>(it->mID, *dynamic_pointer_cast<SphereCollider>(pComponent)));
			it->mComponentMask |= COMPONENT_SPHERECOLLIDER;
			break;
		case COMPONENT_GEOMETRY:
			mGeometries.push_back(pair<int, Geometry>(it->mID, *dynamic_pointer_cast<Geometry>(pComponent)));
			it->mComponentMask |= COMPONENT_GEOMETRY;
			break;
		case COMPONENT_TEXTURE:
			mTextures.push_back(pair<int, Texture>(it->mID, *dynamic_pointer_cast<Texture>(pComponent)));
			it->mComponentMask |= COMPONENT_TEXTURE;
			break;
		case COMPONENT_SHADER:
			mShaders.push_back(pair<int, Shader>(it->mID, *dynamic_pointer_cast<Shader>(pComponent)));
			it->mComponentMask |= COMPONENT_SHADER;
			break;
		case COMPONENT_CAMERA:
			mCameras.push_back(pair<int, Camera>(it->mID, *dynamic_pointer_cast<Camera>(pComponent)));
			it->mComponentMask |= COMPONENT_CAMERA;
			break;
		case COMPONENT_LIGHT:
			mLights.push_back(pair<int, Light>(it->mID, *dynamic_pointer_cast<Light>(pComponent)));
			it->mComponentMask |= COMPONENT_LIGHT;
			break;
		case COMPONENT_GRAVITY:
			mGravities.push_back(pair<int, Gravity>(it->mID, *dynamic_pointer_cast<Gravity>(pComponent)));
			it->mComponentMask |= COMPONENT_GRAVITY;
			break;
		case COMPONENT_AUDIO:
			mAudios.push_back(pair<int, Audio>(it->mID, *dynamic_pointer_cast<Audio>(pComponent)));
			it->mComponentMask |= COMPONENT_AUDIO;
			break;
		case COMPONENT_AI:
			mAIs.push_back(pair<int, AI>(it->mID, *dynamic_pointer_cast<AI>(pComponent)));
			it->mComponentMask |= COMPONENT_AI;
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
	auto it = find_if(mEntities.begin(), mEntities.end(), [&](const Entity& entity) {return entity.mName == pEntityName; });

	//If the iterator is not pointing to the end of the vector, removes the component from the component vector of the appropriate type and modifies the entities component mask appropriately
	if (it != mEntities.end())
	{
		switch (pComponentType)
		{
		case COMPONENT_TRANSFORM:
			mTransforms.erase(remove(mTransforms.begin(), mTransforms.end(), [&](const pair<int, Transform>& pair) {pair.first == it->mID; }));
			break;
		case COMPONENT_VELOCITY:
			mVelocities.erase(remove(mVelocities.begin(), mVelocities.end(), [&](const pair<int, Velocity>& pair) {pair.first == it->mID; }));
			break;
		case COMPONENT_BOXCOLLIDER:
			mBoxColliders.erase(remove(mBoxColliders.begin(), mBoxColliders.end(), [&](const pair<int, BoxCollider>& pair) {pair.first == it->mID; }));
			break;
		case COMPONENT_SPHERECOLLIDER:
			mSphereColliders.erase(remove(mSphereColliders.begin(), mSphereColliders.end(), [&](const pair<int, SphereCollider>& pair) {pair.first == it->mID; }));
			break;
		case COMPONENT_GEOMETRY:
			mGeometries.erase(remove(mGeometries.begin(), mGeometries.end(), [&](const pair<int, Geometry>& pair) {pair.first == it->mID; }));
			break;
		case COMPONENT_TEXTURE:
			mTextures.erase(remove(mTextures.begin(), mTextures.end(), [&](const pair<int, Texture>& pair) {pair.first == it->mID; }));
			break;
		case COMPONENT_SHADER:
			mShaders.erase(remove(mShaders.begin(), mShaders.end(), [&](const pair<int, Shader>& pair) {pair.first == it->mID; }));
			break;
		case COMPONENT_CAMERA:
			mCameras.erase(remove(mCameras.begin(), mCameras.end(), [&](const pair<int, Camera>& pair) {pair.first == it->mID; }));
			break;
		case COMPONENT_LIGHT:
			mLights.erase(remove(mLights.begin(), mLights.end(), [&](const pair<int, Light>& pair) {pair.first == it->mID; }));
			break;
		case COMPONENT_GRAVITY:
			mGravities.erase(remove(mGravities.begin(), mGravities.end(), [&](const pair<int, Gravity>& pair) {pair.first == it->mID; }));
			break;
		case COMPONENT_AUDIO:
			mAudios.erase(remove(mAudios.begin(), mAudios.end(), [&](const pair<int, Audio>& pair) {pair.first == it->mID; }));
			break;
		case COMPONENT_AI:
			mAIs.erase(remove(mAIs.begin(), mAIs.end(), [&](const pair<int, AI>& pair) {pair.first == it->mID; }));
			break;
		}
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="pSystem"></param>
void ECSManager::AddUpdateSystem(const std::shared_ptr<const ISystem> pSystem)
{
}

/// <summary>
/// 
/// </summary>
/// <param name="pSystem"></param>
void ECSManager::AddRenderSystem(const std::shared_ptr<const ISystem> pSystem)
{
}

/// <summary>
/// 
/// </summary>
void ECSManager::ProcessSystems()
{
}

/// <summary>
/// 
/// </summary>
/// <param name="pComponentType"></param>
/// <param name="pEntityName"></param>
/// <returns></returns>
const std::shared_ptr<const IComponent> ECSManager::GetComponent(const ComponentType & pComponentType, const std::string & pEntityName) const
{
	return std::shared_ptr<const IComponent>();
}

/// <summary>
/// 
/// </summary>
/// <param name="pComponentType"></param>
/// <param name="pComponent"></param>
void ECSManager::SetComponent(const ComponentType & pComponentType, const std::shared_ptr<const IComponent> pComponent)
{
}

/// <summary>
/// 
/// </summary>
/// <param name="pComponentType"></param>
/// <param name="pEntityID"></param>
/// <returns></returns>
const std::shared_ptr<const IComponent> ECSManager::GetComponent(const ComponentType & pComponentType, const int & pEntityID) const
{
	return std::shared_ptr<const IComponent>();
}

/// <summary>
/// 
/// </summary>
/// <param name="pComponentType"></param>
/// <param name="pEntityID"></param>
void ECSManager::SetComponent(const ComponentType & pComponentType, const int & pEntityID)
{
}
