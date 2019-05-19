#pragma once
#include <memory>
#include <vector>
#include "Components.h"
#include "ISystem.h"
#include "Entity.h"
#include <algorithm>
#include <string>
#include "ThreadManager.h"
#include <chrono>

class RenderSystem_DX;

class ECSManager
{
private:
	std::shared_ptr<ThreadManager> mThreadManager = ThreadManager::Instance();

	//Entities and free ID list
	std::vector<Entity> mEntities;
	std::vector<int> mFreeEntityIDs;
	int mEntityID;
	int MAX_ENTITIES;

	//Components
	std::vector<AI> mAIs;
	std::vector<Audio> mAudios;
	std::vector<BoxCollider> mBoxColliders;
	std::vector<Camera> mCameras;
	std::vector<Colour> mColours;
	std::vector<Geometry> mGeometries;
	std::vector<Gravity> mGravities;
	std::vector<Light> mLights;
	std::vector<Ray> mRays;
	std::vector<Shader> mShaders;
	std::vector<SphereCollider> mSphereColliders;
	std::vector<Texture> mTextures;
	std::vector<Transform> mTransforms;
	std::vector<Velocity> mVelocities;

	//Custom components
	std::vector<void*> mCustomComponentVectors;
	std::vector<std::vector<unsigned short>*> mCustomComponentEntityMaps;
	std::vector<CustomComponent*> mCustomComponentTypes;
	std::vector<int> mCustomComponentMasks;

	//Entity-Component maps
	std::vector<unsigned short> mAIEntityMap;
	std::vector<unsigned short> mAudioEntityMap;
	std::vector<unsigned short> mBoxColliderEntityMap;
	std::vector<unsigned short> mCameraEntityMap;
	std::vector<unsigned short> mColourEntityMap;
	std::vector<unsigned short> mGeometryEntityMap;
	std::vector<unsigned short> mGravityEntityMap;
	std::vector<unsigned short> mLightEntityMap;
	std::vector<unsigned short> mRayEntityMap;
	std::vector<unsigned short> mShaderEntityMap;
	std::vector<unsigned short> mSphereColliderEntityMap;
	std::vector<unsigned short> mTextureEntityMap;
	std::vector<unsigned short> mTransformEntityMap;
	std::vector<unsigned short> mVelocityEntityMap;

	//Systems
	std::shared_ptr<ISystem> mRenderSystem;
	std::vector<std::shared_ptr<ISystem>> mUpdateSystems;
	std::vector<std::shared_ptr<ISystem>> mNetworkSystems;

	//Render and network threads
	Task* mRenderTask = nullptr;
	int mRenderingFrequency;
	std::chrono::high_resolution_clock::time_point mRenderStart;
	std::chrono::high_resolution_clock::time_point mRenderFinish;
	std::chrono::nanoseconds mRenderTime;

	//Entity management
	void AssignEntity(const Entity& pEntity);
	void ReAssignEntity(const Entity& pEntity);

	//Private constructor for singleton pattern
	ECSManager();

public:
	~ECSManager();

	//Singleton pattern
	//Deleted copy constructor and assignment operator so no copies of the singleton instance can be made
	ECSManager(ECSManager const&) = delete;
	ECSManager& operator=(ECSManager const&) = delete;
	static std::shared_ptr<ECSManager> Instance();

	//Frequencies get/sets
	const int& RenderingFrequency();

	//Entity creation
	void SetMaxEntities(const int pEntityCount);
	const int MaxEntities();
	const int CreateEntity();
	void DestroyEntity(const int pEntityID);

	//System management
	void AddUpdateSystem(std::shared_ptr<ISystem> pSystem);
	void AddRenderSystem(std::shared_ptr<ISystem> pSystem);
	void ProcessSystems();

	template<class T>
	/// <summary>
	/// Creates a new custom component of type T
	/// </summary>
	/// <param name="pMask">Bitmask for the new custom component type</param>
	void CreateCustomComponent(const int pMask)
	{
		//Add new type to types list
		mCustomComponentTypes.push_back(new T());

		//Add new mask to masks list
		mCustomComponentMasks.push_back(pMask);

		//Create vector for new component type
		std::vector<T>* newVector = new std::vector<T>();
		mCustomComponentVectors.push_back(static_cast<void*>(newVector));

		//Create vector for new component types entity component map
		std::vector<unsigned short>* newMapVector = new std::vector<unsigned short>();
		newMapVector->resize(MAX_ENTITIES);
		mCustomComponentEntityMaps.push_back(newMapVector);
	}

	//Add methods for components
	void AddAIComp(const AI& pAI, const int pEntityID);
	void AddAudioComp(const Audio& pAudio, const int pEntityID);
	void AddBoxColliderComp(const BoxCollider& pBoxCollider, const int pEntityID);
	void AddCameraComp(const Camera& pCamera, const int pEntityID);
	void AddColourComp(const Colour& pColour, const int pEntityID);
	void AddGeometryComp(const Geometry& pGeometry, const int pEntityID);
	void AddGravityComp(const Gravity& pGravity, const int pEntityID);
	void AddLightComp(const Light& pLight, const int pEntityID);
	void AddRayComp(const Ray& pRay, const int pEntityID);
	void AddShaderComp(const Shader& pShader, const int pEntityID);
	void AddSphereColliderComp(const SphereCollider& pSphereCollider, const int pEntityID);
	void AddTextureComp(const Texture& pTexture, const int pEntityID);
	void AddTransformComp(const Transform& pTransform, const int pEntityID);
	void AddVelocityComp(const Velocity& pVelocity, const int pEntityID);


	template <class T>
	/// <summary>
	/// Add a custom component of type T to the given entity
	/// </summary>
	/// <param name="pComponent">Component to add</param>
	/// <param name="pEntityID">ID of given entity</param>
	/// <returns>Bool representing whether the addition of this custom component was successful or not</returns>
	bool AddCustomComponent(const T& pComponent, const int pEntityID)
	{
		//Loop through custom types to find matching type
		for (int i = 0; i < mCustomComponentTypes.size(); i++)
		{
			//Check if type matches
			if (dynamic_cast<T*>(mCustomComponentTypes[i]))
			{
				//Retrieve vector that contains this component type and then add new component to vector
				std::vector<T>* componentVector = static_cast<std::vector<T>*>(mCustomComponentVectors[i]);
				componentVector->push_back(pComponent);

				//Retrieve vector that contains this component types entity-component map and add index of component
				std::vector<unsigned short>* componentEntityMapVector = mCustomComponentEntityMaps[i];
				(*componentEntityMapVector)[pEntityID] = static_cast<unsigned short>(componentVector->size() - 1);

				//Adjust entities mask to contain mask of new component
				Entity* entity = &mEntities[pEntityID];
				entity->componentMask |= mCustomComponentMasks[i];
				AssignEntity(*entity);

				return true;
			}
		}
		return false;
	};

	//Remove methods for components
	void RemoveAIComp(const int pEntityID);
	void RemoveAudioComp(const int pEntityID);
	void RemoveBoxColliderComp(const int pEntityID);
	void RemoveCameraComp(const int pEntityID);
	void RemoveColourComp(const int pEntityID);
	void RemoveGeometryComp(const int pEntityID);
	void RemoveGravityComp(const int pEntityID);
	void RemoveLightComp(const int pEntityID);
	void RemoveRayComp(const int pEntityID);
	void RemoveShaderComp(const int pEntityID);
	void RemoveSphereColliderComp(const int pEntityID);
	void RemoveTextureComp(const int pEntityID);
	void RemoveTransformComp(const int pEntityID);
	void RemoveVelocityComp(const int pEntityID);

	template <class T>
	/// <summary>
	/// Removes a custom component of type T from the given entity
	/// </summary>
	/// <param name="pEntityID">ID of the given entity</param>
	/// <returns>Bool representing whether the removal of this custom component was successful or not</returns>
	bool RemoveCustomComponent(const int pEntityID)
	{
		//Loop through custom types to find matching type
		for (int i = 0; i < mCustomComponentTypes.size(); i++)
		{
			//Checks if entity actually owns a component of this type
			if ((mEntities[pEntityID].componentMask & mCustomComponentMasks[i]) == mCustomComponentMasks[i])
			{
				//Check if type matches
				if (dynamic_cast<T*>(mCustomComponentTypes[i]))
				{
					//Retrieve vector that contains this component type and vector that contains this component types entity component map
					std::vector<unsigned short>* componentEntityMapVector = mCustomComponentEntityMaps[i];
					std::vector<T>* componentVector = static_cast<std::vector<T>*>(mCustomComponentVectors[i]);

					//Replace the removed component with back element
					(*componentVector)[(*componentEntityMapVector)[pEntityID]] = componentVector->back();

					//Set new index of component in the entity component map		
					(*componentEntityMapVector)[componentVector->size() - 1] = (*componentEntityMapVector)[pEntityID];

					//Pop back element
					componentVector->pop_back();

					//Adjust entities mask to no longer contain mask of removed component
					Entity* entity = &mEntities[pEntityID];
					entity->componentMask = entity->componentMask &= ~mCustomComponentMasks[i]; //Performs a bitwise & between the entities mask and the bitwise complement of the components mask
					ReAssignEntity(*entity);

					return true;
				}
			}
		}
		return false;
	}

	//Accessors
	AI* const AIComp(const int pEntityID);
	Audio* const AudioComp(const int pEntityID);
	BoxCollider* const BoxColliderComp(const int pEntityID);
	Camera* const CameraComp(const int pEntityID);
	Colour* const ColourComp(const int pEntityID);
	Geometry* const GeometryComp(const int pEntityID);
	Gravity* const GravityComp(const int pEntityID);
	Light* const LightComp(const int pEntityID);
	Ray* const RayComp(const int pEntityID);
	Shader* const ShaderComp(const int pEntityID);
	SphereCollider* const SphereColliderComp(const int pEntityID);
	Texture* const TextureComp(const int pEntityID);
	Transform* const TransformComp(const int pEntityID);
	Velocity* const VelocityComp(const int pEntityID);

	template <class T>
	/// <summary>
	/// Get component of type T for the given entity
	/// </summary>
	/// <param name="pEntityID">ID of given entity</param>
	/// <returns>Modifiable handle to the component of type T</returns>
	T* const GetCustomComponent(const int pEntityID)
	{
		//Loop through custom types to find matching type
		for (int i = 0; i < mCustomComponentTypes.size(); i++)
		{
			//Checks if entity actually owns a component of this type
			if ((mEntities[pEntityID].componentMask & mCustomComponentMasks[i]) == mCustomComponentMasks[i])
			{
				//Check if type matches
				if (dynamic_cast<T*>(mCustomComponentTypes[i]))
				{
					//Retrieve vector that contains this component type and vector that contains this component types entity component map
					std::vector<unsigned short>* componentEntityMapVector = mCustomComponentEntityMaps[i];
					std::vector<T>* componentVector = static_cast<std::vector<T>*>(mCustomComponentVectors[i]);

					//Gets the index of the component from the map, then retrieves the component from the component vector
					return static_cast<T*>(&((*componentVector)[(*componentEntityMapVector)[pEntityID]]));
				}
			}
		}
		return nullptr;
	};
};
