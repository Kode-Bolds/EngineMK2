#pragma once
#include <memory>
#include "ECSManager.h"
#include "KodeboldsMath.h"
#include "CustomCollisionMask.h"

namespace EntitySpawner
{
	static std::shared_ptr<ECSManager> entitySpawnerEcsManager = ECSManager::Instance();

	static int SpawnLaser(const KodeboldsMath::Vector4& pPosition, const KodeboldsMath::Vector4& pScale, const KodeboldsMath::Vector4& pRotation, const KodeboldsMath::Vector4& pColour,
		const KodeboldsMath::Vector4& pAcceleration, const float& pMaxSpeed, const KodeboldsMath::Vector3& pBoxMin, const KodeboldsMath::Vector3& pBoxMax)
	{
		int ID = entitySpawnerEcsManager->CreateEntity();

		//Geometry component
		Geometry geo{ L"cube.obj" };
		entitySpawnerEcsManager->AddGeometryComp(geo, ID);

		//Shader component
		Shader shader{ L"defaultShader.fx" };
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

		Texture tex{};
		entitySpawnerEcsManager->AddTextureComp(tex, ID);


		//Velocity component
		Velocity vel{ pAcceleration, KodeboldsMath::Vector4(), pMaxSpeed };
		entitySpawnerEcsManager->AddVelocityComp(vel, ID);

		//Colour component
		Colour colour{ pColour };
		entitySpawnerEcsManager->AddColourComp(colour, ID);

		//BoxCollider component
		BoxCollider box{ pBoxMin, pBoxMax, CustomCollisionMask::LASER };
		entitySpawnerEcsManager->AddBoxColliderComp(box, ID);

		return ID;
	}
};