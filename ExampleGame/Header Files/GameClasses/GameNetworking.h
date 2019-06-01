#pragma once
#include "NetworkManager.h"
#include "ECSManager.h"

class GameNetworking
{
private:
	std::shared_ptr<ECSManager> mEcsManager = ECSManager::Instance();
	std::shared_ptr<NetworkManager> mNetworkManager = NetworkManager::Instance();

public:
	GameNetworking();
	~GameNetworking();

	void ProcessMessages();
};