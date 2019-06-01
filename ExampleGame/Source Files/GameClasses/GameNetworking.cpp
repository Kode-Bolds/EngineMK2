#include "GameNetworking.h"

/// <summary>
/// 
/// </summary>
GameNetworking::GameNetworking()
{
}

/// <summary>
/// 
/// </summary>
GameNetworking::~GameNetworking()
{
}

/// <summary>
/// 
/// </summary>
void GameNetworking::ProcessMessages()
{
	std::queue<std::string> messages =  mNetworkManager->ReadMessages();
	int messageCount = messages.size();

	for (int i = 0; i < messageCount; i++)
	{
		std::string message = messages.front();

		//Player connect message
		if (message[0] == 'C')
		{

		}

		//Player move message
		if (message[0] == 'M')
		{

		}

		//Player fire message
		if (message[0] == 'F')
		{

		}

		//Gravity asteroid message
		if (message[0] == 'G')
		{

		}
	}
}
