#pragma once
#include "NetworkManager.h"
#include "ECSManager.h"
#include "KodeboldsMath.h"
#include "SceneManager.h"
#include "EntitySpawner.h"
#include "CustomCollisionMask.h"

class GameNetworking
{
private:
	std::shared_ptr<ECSManager> mEcsManager = ECSManager::Instance();
	std::shared_ptr<NetworkManager> mNetworkManager = NetworkManager::Instance();
	std::shared_ptr<SceneManager> mSceneManager = SceneManager::Instance();

	int mPlayerCount;
	int mPlayerNumber;
	std::queue<int> mNewBullets;

	void RotateAroundPoint(const int pEntity, const KodeboldsMath::Vector4& pAxis, const KodeboldsMath::Vector4& pPoint, const float& pAngle);

public:
	GameNetworking();
	~GameNetworking();

	void ProcessMessages();
	const int PlayerNumber();
	std::queue<int>& NewBullets();
};