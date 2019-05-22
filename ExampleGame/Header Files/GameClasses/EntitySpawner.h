#pragma once
#include <memory>
#include <string>
#include "ECSManager.h"
#include "KodeboldsMath.h"
#include "CustomCollisionMask.h"

namespace EntitySpawner
{
	static std::shared_ptr<ECSManager> entitySpawnerEcsManager = ECSManager::Instance();

	/// <summary>
	///
	/// </summary>
	/// <param name="pPosition"></param>
	/// <param name="pScale"></param>
	/// <param name="pRotation"></param>
	/// <param name="pColour"></param>
	/// <param name="pAcceleration"></param>
	/// <param name="pMaxSpeed"></param>
	/// <param name="pBoxMin"></param>
	/// <param name="pBoxMax"></param>
	/// <param name="pIgnoreCollisionMask"></param>
	/// <returns></returns>
	static int SpawnLaser(const KodeboldsMath::Vector4& pPosition, const KodeboldsMath::Vector4& pScale, const KodeboldsMath::Vector4& pRotation, const KodeboldsMath::Vector4& pColour,
		const KodeboldsMath::Vector4& pAcceleration, const float& pMaxSpeed, const KodeboldsMath::Vector3& pBoxMin, const KodeboldsMath::Vector3& pBoxMax, const int pIgnoreCollisionMask)
	{
		int ID = entitySpawnerEcsManager->CreateEntity();

		//Geometry component
		Geometry geo{ L"cube.obj" };
		entitySpawnerEcsManager->AddGeometryComp(geo, ID);

		//Shader component
		Shader shader{ L"errorShader.fx", BlendState::ALPHABLEND, CullState::BACK, DepthState::LESSEQUAL };
		entitySpawnerEcsManager->AddShaderComp(shader, ID);

		//Light component
		Light light{ pColour };
		entitySpawnerEcsManager->AddLightComp(light, ID);

		//Transform component
		Transform trans{};
		trans.scale = pScale;
		trans.rotation = pRotation;
		trans.translation = pPosition;
		entitySpawnerEcsManager->AddTransformComp(trans, ID);

		//Texture component
		Texture tex{};
		tex.diffuse = L"stones.dds";
		tex.normal = L"stones_NM_height.dds";
		entitySpawnerEcsManager->AddTextureComp(tex, ID);

		//Velocity component
		Velocity vel{ pAcceleration, KodeboldsMath::Vector4(), pMaxSpeed };
		entitySpawnerEcsManager->AddVelocityComp(vel, ID);

		//Colour component
		Colour colour{ pColour };
		entitySpawnerEcsManager->AddColourComp(colour, ID);

		//BoxCollider component
		BoxCollider box{ pBoxMin, pBoxMax, CustomCollisionMask::LASER, pIgnoreCollisionMask };
		entitySpawnerEcsManager->AddBoxColliderComp(box, ID);

		return ID;
	}

	/// <summary>
	///
	/// </summary>
	/// <param name="pPosition"></param>
	/// <param name="pScale"></param>
	/// <param name="pRotation"></param>
	/// <param name="pMaxSpeed"></param>
	/// <param name="pBoxMin"></param>
	/// <param name="pBoxMax"></param>
	/// <param name="pCollisionMask"></param>
	/// <param name="pIgnoreCollisionMask"></param>
	/// <param name="pDiffuse"></param>
	/// <param name="pNormal"></param>
	/// <returns></returns>
	static int SpawnShip(const KodeboldsMath::Vector4& pPosition, const KodeboldsMath::Vector4& pScale, const KodeboldsMath::Vector4& pRotation, const float& pMaxSpeed,
		const KodeboldsMath::Vector3& pBoxMin, const KodeboldsMath::Vector3& pBoxMax, const int pCollisionMask, const int pIgnoreCollisionMask, const std::wstring& pDiffuse,
		const std::wstring& pNormal)
	{
		int ID = entitySpawnerEcsManager->CreateEntity();

		//Geometry component
		Geometry geo{ L"ship.obj" };
		entitySpawnerEcsManager->AddGeometryComp(geo, ID);

		//Shader component
		Shader shader{ L"defaultShader.fx" , BlendState::NOBLEND, CullState::BACK, DepthState::NONE };
		entitySpawnerEcsManager->AddShaderComp(shader, ID);

		//Texture component
		Texture texture{ pDiffuse, pNormal, L"" };
		entitySpawnerEcsManager->AddTextureComp(texture, ID);

		//Transform component
		Transform trans{};
		trans.scale = pScale;
		trans.rotation = pRotation;
		trans.translation = pPosition;
		entitySpawnerEcsManager->AddTransformComp(trans, ID);

		//Velocity component
		Velocity vel{};
		vel.maxSpeed = pMaxSpeed;
		entitySpawnerEcsManager->AddVelocityComp(vel, ID);

		//BoxCollider component
		BoxCollider box{ pBoxMin, pBoxMax, pCollisionMask, pIgnoreCollisionMask };
		entitySpawnerEcsManager->AddBoxColliderComp(box, ID);

		return ID;
	}

	/// <summary>
	///
	/// </summary>
	/// <param name="pPosition"></param>
	/// <param name="pScale"></param>
	/// <param name="pRotation"></param>
	/// <param name="pRadius"></param>
	/// <param name="pIgnoreCollisionMask"></param>
	/// <param name="pDiffuse"></param>
	/// <param name="pNormal"></param>
	/// <returns></returns>
	static int SpawnAsteroid(const KodeboldsMath::Vector4& pPosition, const KodeboldsMath::Vector4& pScale, const KodeboldsMath::Vector4& pRotation, const float& pRadius,
		const int pIgnoreCollisionMask, const std::wstring& pDiffuse, const std::wstring& pNormal)
	{
		int ID = entitySpawnerEcsManager->CreateEntity();

		//Geometry component
		Geometry geo{ L"sphere.obj" };
		entitySpawnerEcsManager->AddGeometryComp(geo, ID);

		//Shader component
		Shader shader{ L"defaultShader.fx", BlendState::NOBLEND, CullState::BACK, DepthState::NONE };
		entitySpawnerEcsManager->AddShaderComp(shader, ID);

		//Texture component
		Texture texture{ pDiffuse, pNormal, L"" };
		entitySpawnerEcsManager->AddTextureComp(texture, ID);

		//Transform component
		Transform trans{};
		trans.scale = pScale;
		trans.rotation = pRotation;
		trans.translation = pPosition;
		entitySpawnerEcsManager->AddTransformComp(trans, ID);

		//SphereCollider component
		SphereCollider sphere{ pRadius, CustomCollisionMask::ASTEROID, pIgnoreCollisionMask };
		entitySpawnerEcsManager->AddSphereColliderComp(sphere, ID);

		return ID;
	}

	static int SpawnLaserGun(const KodeboldsMath::Vector4& pPosition, const KodeboldsMath::Vector4& pScale, const KodeboldsMath::Vector4& pRotation, const std::wstring& pDiffuse,
		const std::wstring& pNormal, const float& pMaxSpeed)
	{
		int ID = entitySpawnerEcsManager->CreateEntity();

		//Geometry component
		Geometry geo{ L"laser_gun.obj" };
		entitySpawnerEcsManager->AddGeometryComp(geo, ID);

		//Shader component
		Shader shader{ L"defaultShader.fx", BlendState::NOBLEND, CullState::BACK, DepthState::NONE };
		entitySpawnerEcsManager->AddShaderComp(shader, ID);

		//Texture component
		Texture texture{ pDiffuse, pNormal, L"" };
		entitySpawnerEcsManager->AddTextureComp(texture, ID);

		//Transform component
		Transform trans{};
		trans.scale = pScale;
		trans.rotation = pRotation;
		trans.translation = pPosition;
		entitySpawnerEcsManager->AddTransformComp(trans, ID);

		//Velocity component
		Velocity vel{};
		vel.maxSpeed = pMaxSpeed;
		entitySpawnerEcsManager->AddVelocityComp(vel, ID);

		//Gravity component
		Gravity grav{};
		entitySpawnerEcsManager->AddGravityComp(grav, ID);

		return ID;
	}

	static int SpawnCamera(const KodeboldsMath::Vector4& pPosition, const KodeboldsMath::Vector4& pScale, const KodeboldsMath::Vector4& pRotation, const float& pFOV,
		const int pNear, const int pFar, const float& pMaxSpeed)
	{
		int ID = entitySpawnerEcsManager->CreateEntity();

		//Camera component
		Camera cam{ pFOV, pNear, pFar, false };
		entitySpawnerEcsManager->AddCameraComp(cam, ID);

		//Transform component
		Transform trans{};
		trans.translation = pPosition;
		trans.scale = pScale;
		trans.rotation = pRotation;
		entitySpawnerEcsManager->AddTransformComp(trans, ID);

		//Velocity component
		Velocity vel{};
		vel.maxSpeed = pMaxSpeed;
		entitySpawnerEcsManager->AddVelocityComp(vel, ID);

		return ID;
	}

	static int SpawnPlayer(const KodeboldsMath::Vector4& pPosition, const KodeboldsMath::Vector4& pScale, const KodeboldsMath::Vector4& pRotation, const float& pFOV,
		const int pNear, const int pFar, const float& pMaxSpeed, const KodeboldsMath::Vector3& pBoxMin, const KodeboldsMath::Vector3& pBoxMax, const int pCollisionMask, const int pIgnoreCollisionMask)
	{
		int ID = entitySpawnerEcsManager->CreateEntity();

		//Camera component
		Camera cam{ pFOV, pNear, pFar, false };
		entitySpawnerEcsManager->AddCameraComp(cam, ID);

		//Transform component
		Transform trans{};
		trans.scale = pScale;
		trans.rotation = pRotation;
		trans.translation = pPosition;
		entitySpawnerEcsManager->AddTransformComp(trans, ID);

		//Velocity component
		Velocity vel{};
		vel.maxSpeed = pMaxSpeed;
		entitySpawnerEcsManager->AddVelocityComp(vel, ID);

		//BoxCollider component
		BoxCollider box{ pBoxMin, pBoxMax, pCollisionMask, pIgnoreCollisionMask };
		entitySpawnerEcsManager->AddBoxColliderComp(box, ID);

		//Gravity component
		Gravity grav{};
		entitySpawnerEcsManager->AddGravityComp(grav, ID);

		return ID;
	}
};
