#pragma once
#include <memory>
#include <vector>
#include "Components.h"
#include "ISystem.h"
#include "Entity.h"
#include <algorithm>
#include <string>

class ECSManager
{
private:
	std::vector<Entity> mEntities;
	std::vector<std::pair<std::string, int>> mEntityNames;
	std::vector<std::pair<int, Transform>> mTransforms;
	std::vector<std::pair<int, Velocity>> mVelocities;
	std::vector<std::pair<int, BoxCollider>> mBoxColliders;
	std::vector<std::pair<int, SphereCollider>> mSphereColliders;
	std::vector<std::pair<int, Geometry>> mGeometries;
	std::vector<std::pair<int, Texture>> mTextures;
	std::vector<std::pair<int, Shader>> mShaders;
	std::vector<std::pair<int, Camera>> mCameras;
	std::vector<std::pair<int, Light>> mLights;
	std::vector<std::pair<int, Gravity>> mGravities;
	std::vector<std::pair<int, Audio>> mAudios;
	std::vector<std::pair<int, AI>> mAIs;
	std::vector<std::shared_ptr<ISystem>> mRenderSystems;
	std::vector<std::shared_ptr<ISystem>> mUpdateSystems;

	ECSManager();

	void AssignEntity(const Entity& pEntity);
	void RemoveEntity(const Entity& pEntity);

public:
	~ECSManager();

	//Deleted so no copies of the singleton instance can be made
	ECSManager(ECSManager const&) = delete;
	ECSManager& operator=(ECSManager const&) = delete;
	
	/// <summary>
	/// Creates a singleton instance of ECS Manager if one hasn't been created before
	/// Returns pointer to the instance of ECS Manager
	/// </summary>
	/// <returns>Shared pointer to the ECS Manager instance</returns>
	static std::shared_ptr<ECSManager> Instance()
	{
		static std::shared_ptr<ECSManager> mInstance{new ECSManager};
		return mInstance;
	}

	void CreateEntity(const std::string& pEntityName);
	void DestroyEntity(const std::string& pEntityName);
	void AddComponent(const ComponentType& pComponentType, const std::shared_ptr<const IComponent> pComponent, const std::string& pEntityName);
	void RemoveComponent(const ComponentType& pComponentType, const std::string& pEntityName);
	void AddUpdateSystem(const std::shared_ptr<ISystem> pSystem);
	void AddRenderSystem(const std::shared_ptr<ISystem> pSystem);
	void ProcessSystems();
	const std::shared_ptr<const IComponent> GetComponent(const ComponentType& pComponentType, const std::string& pEntityName) const;
	void SetComponent(const ComponentType& pComponentType, const std::shared_ptr<const IComponent> pComponent, const std::string pEntityName);
	const std::shared_ptr<const IComponent> GetComponent(const ComponentType& pComponentType, const int& pEntityID) const;
	void SetComponent(const ComponentType& pComponentType, const std::shared_ptr<const IComponent> pComponent, const int& pEntityID);
};
