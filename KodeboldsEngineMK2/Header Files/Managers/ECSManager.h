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
	int mEntityID;

	ECSManager();

	//Entity management
	void AssignEntity(const Entity& pEntity);
	Entity* const FindEntityByName(const std::string& pEntityName);

public:
	~ECSManager();

	//Singleton pattern
	//Deleted copy constructor and assignment operator so no copies of the singleton instance can be made
	ECSManager(ECSManager const&) = delete;
	ECSManager& operator=(ECSManager const&) = delete;	
	static std::shared_ptr<ECSManager> Instance();

	//Entity creation
	void CreateEntity(const std::string& pEntityName);
	void DestroyEntity(const std::string& pEntityName);

	//System management
	void AddUpdateSystem(std::shared_ptr<ISystem> pSystem);
	void AddRenderSystem(std::shared_ptr<ISystem> pSystem);
	void ProcessSystems();

	//Add/Remove methods for components
	void AddAIComp(const AI& pAI, const std::string& pEntityName);
	void RemoveAIComp(const std::string& pEntityName);
	void AddAudioComp(const Audio& pAudio, const std::string& pEntityName);
	void RemoveAudioComp(const std::string& pEntityName);
	void AddBoxColliderComp(const BoxCollider& pBoxCollider, const std::string& pEntityName);
	void RemoveBoxColliderComp(const std::string& pEntityName);
	void AddCameraComp(const Camera& pCamera, const std::string& pEntityName);
	void RemoveCameraComp(const std::string& pEntityName);
	void AddGeometryComp(const Geometry& pGeometry, const std::string& pEntityName);
	void RemoveGeometryComp(const std::string& pEntityName);
	void AddGravityComp(const Gravity& pGravity, const std::string& pEntityName);
	void RemoveGravityComp(const std::string& pEntityName);
	void AddLightComp(const Light& pLight, const std::string& pEntityName);
	void RemoveLightComp(const std::string& pEntityName);
	void AddShaderComp(const Shader& pShader, const std::string& pEntityName);
	void RemoveShaderComp(const std::string& pEntityName);
	void AddSphereColliderComp(const SphereCollider& pSphereCollider, const std::string& pEntityName);
	void RemoveSphereColliderComp(const std::string& pEntityName);
	void AddTextureComp(const Texture& pTexture, const std::string& pEntityName);
	void RemoveTextureComp(const std::string& pEntityName);
	void AddTransformComp(const Transform& pTransform, const std::string& pEntityName);
	void RemoveTransformComp(const std::string& pEntityName);
	void AddVelocityComp(const Velocity& pVelocity, const std::string& pEntityName);
	void RemoveVelocityComp(const std::string& pEntityName);

	//Get/Set methods return non-const refs
	AI& AIComp(const int& pEntityID);
	AI& AIComp(const std::string& pEntityName);
	Audio& AudioComp(const int& pEntityID);
	Audio& AudioComp(const std::string& pEntityName);
	BoxCollider& BoxColliderComp(const int& pEntityID);
	BoxCollider& BoxColliderComp(const std::string& pEntityName);
	Camera& CameraComp(const int& pEntityID);
	Camera& CameraComp(const std::string pEntityName);
	Geometry& GeometryComp(const int& pEntityID);
	Geometry& GeometryComp(const std::string& pEntityName);
	Gravity& GravityComp(const int& pEntityID);
	Gravity& GravityComp(const std::string& pEntityName);
	Light& LightComp(const int& pEntityID);
	Light& LightComp(const std::string& pEntityName);
	Shader& ShaderComp(const int& pEntityID);
	Shader& ShaderComp(const std::string& pEntityName);
	SphereCollider& SphereColliderComp(const int& pEntityID);
	SphereCollider& SphereColliderComp(const std::string& pEntityName);
	Texture& TextureComp(const int& pEntityID);
	Texture& TextureComp(const std::string& pEntityName);
	Transform& TransformComp(const int& pEntityID);
	Transform& TransformComp(const std::string& pEntityName);
	Velocity& VelocityComp(const int& pEntityID);
	Velocity& VelocityComp(const std::string& pEntityName);
};
