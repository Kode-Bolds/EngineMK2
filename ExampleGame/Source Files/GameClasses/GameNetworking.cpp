#include "GameNetworking.h"

using namespace KodeboldsMath;

void GameNetworking::RotateAroundPoint(const int pEntity, const KodeboldsMath::Vector4 & pAxis, const KodeboldsMath::Vector4 & pPoint, const float & pAngle)
{
	const float angleInRadians = DegreesToRadians(pAngle);

	auto translateTo = TranslationMatrix(pPoint);
	auto rotation = RotationMatrixAxis(angleInRadians * mSceneManager->DeltaTime(), pAxis);
	auto translateBack = TranslationMatrix(pPoint * -1);

	mEcsManager->TransformComp(pEntity)->transform *= translateTo * rotation * translateBack;
}

/// <summary>
/// 
/// </summary>
GameNetworking::GameNetworking()
	:mPlayerNumber(1)
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
	std::queue<std::string> messages = mNetworkManager->ReadMessages();
	int messageCount = messages.size();

	for (int i = 0; i < messageCount; i++)
	{
		std::string message = messages.front();

		//Player connect message
		if (message[0] == 'C' && message[1] != 'R')
		{
			mPlayerCount++;
			mNetworkManager->AddMessage("CR");
		}

		//Player connect response message
		if (message[0] == 'C' && message[1] == 'R')
		{
			mPlayerCount++;
			mPlayerNumber = 2;
		}

		//Accelerate player up
		if (message[0] == 'U' && message[1] != 'R')
		{
			int ID = static_cast<int>(message[1]) - 48;
			mEcsManager->VelocityComp(ID)->acceleration += Vector4(0, 1, 0, 0) * 20.0f;
		}
		//Remove up acceleration
		if (message[0] == 'U' && message[1] == 'R')
		{
			int ID = static_cast<int>(message[2]) - 48;
			mEcsManager->VelocityComp(ID)->acceleration -= Vector4(0, 1, 0, 0) * 20.0f;
		}

		//Accelerate player down
		if (message[0] == 'D' && message[1] != 'R')
		{
			int ID = static_cast<int>(message[1]) - 48;
			mEcsManager->VelocityComp(ID)->acceleration += Vector4(0, -1, 0, 0) * 20.0f;
		}
		//Remove down acceleration
		if (message[0] == 'D' && message[1] == 'R')
		{
			int ID = static_cast<int>(message[2]) - 48;
			mEcsManager->VelocityComp(ID)->acceleration -= Vector4(0, -1, 0, 0) * 20.0f;
		}

		//Accelerate player right
		if (message[0] == 'R' && message[1] != 'R')
		{
			int ID = static_cast<int>(message[1]) - 48;
			mEcsManager->VelocityComp(ID)->acceleration += Vector4(1, 0, 0, 0) * 20.0f;
		}
		//Remove right acceleration
		if (message[0] == 'R' && message[1] == 'R')
		{
			int ID = static_cast<int>(message[2]) - 48;
			mEcsManager->VelocityComp(ID)->acceleration -= Vector4(1, 0, 0, 0) * 20.0f;
		}

		//Accelerate player left
		if (message[0] == 'L' && message[1] != 'R')
		{
			int ID = static_cast<int>(message[1]) - 48;
			mEcsManager->VelocityComp(ID)->acceleration += Vector4(-1, 0, 0, 0) * 20.0f;
		}
		//Remove left acceleration
		if (message[0] == 'L' && message[1] == 'R')
		{
			int ID = static_cast<int>(message[2]) - 48;
			mEcsManager->VelocityComp(ID)->acceleration -= Vector4(-1, 0, 0, 0) * 20.0f;
		}

		//Accelerate player forward
		if (message[0] == 'F' && message[1] != 'R')
		{
			int ID = static_cast<int>(message[1]) - 48;
			mEcsManager->VelocityComp(ID)->acceleration += Vector4(0, 0, 1, 0) * 20.0f;
		}
		//Remove forward acceleration
		if (message[0] == 'F' && message[1] == 'R')
		{
			int ID = static_cast<int>(message[2]) - 48;
			mEcsManager->VelocityComp(ID)->acceleration -= Vector4(0, 0, 1, 0) * 20.0f;
		}

		//Accelerate player back
		if (message[0] == 'B' && message[1] != 'R')
		{
			int ID = static_cast<int>(message[1]) - 48;
			mEcsManager->VelocityComp(ID)->acceleration += Vector4(0, 0, -1, 0) * 20.0f;
		}
		//Remove back acceleration
		if (message[0] == 'B' && message[1] == 'R')
		{
			int ID = static_cast<int>(message[2]) - 48;
			mEcsManager->VelocityComp(ID)->acceleration -= Vector4(0, 0, -1, 0) * 20.0f;
		}

		//Rotate ship
		if (message[0] == 'S' && message[1] == 'R')
		{
			int ID = static_cast<int>(message[2]) - 48;
			int ID2 = static_cast<int>(message[3]) - 48;

			//Split the message up on the delimiter
			std::vector<std::string> splitString;
			size_t start;
			size_t end = 0;
			const char delim = ':';

			while ((start = message.find_first_not_of(delim, end)) != std::string::npos)
			{
				end = message.find(delim, start);
				splitString.push_back(message.substr(start, end - start));
			}

			//Y rotation
			mEcsManager->TransformComp(ID)->transform *= RotationMatrixAxis(DegreesToRadians(std::stof(splitString[1]) * 10.0f) * mSceneManager->DeltaTime(), Vector4(0, 1, 0, 1));
			RotateAroundPoint(ID2, Vector4(0, 1, 0, 0), Vector4(0, -40, 75, 0), std::stof(splitString[1]) * 10.0f);

			//X rotation
			mEcsManager->TransformComp(ID)->transform *= RotationMatrixAxis(DegreesToRadians(std::stof(splitString[2]) * 10.0f) * mSceneManager->DeltaTime(), Vector4(1, 0, 0, 1));
			RotateAroundPoint(ID2, Vector4(1, 0, 0, 0), Vector4(0, -40, 75, 0), std::stof(splitString[2]) * 10.0f);
		}

		//Rotate player
		if (message[0] == 'P' && message[1] == 'R')
		{
			int ID = static_cast<int>(message[2]) - 48;
			int ID2 = static_cast<int>(message[3]) - 48;

			//Split the message up on the delimiter
			std::vector<std::string> splitString;
			size_t start;
			size_t end = 0;
			const char delim = ':';

			while ((start = message.find_first_not_of(delim, end)) != std::string::npos)
			{
				end = message.find(delim, start);
				splitString.push_back(message.substr(start, end - start));
			}

			//Y rotation
			mEcsManager->TransformComp(ID)->transform *= RotationMatrixAxis(DegreesToRadians(std::stof(splitString[1]) * 10.0f) * mSceneManager->DeltaTime(), Vector4(0, 1, 0, 1));
			RotateAroundPoint(ID2, Vector4(0, 1, 0, 0), Vector4(0, -40, 75, 0), std::stof(splitString[1]) * 10.0f);
		}

		//Rotate camera
		if (message[0] == 'N')
		{
			int ID = static_cast<int>(message[2]) - 48;

			//Split the message up on the delimiter
			std::vector<std::string> splitString;
			size_t start;
			size_t end = 0;
			const char delim = ':';

			while ((start = message.find_first_not_of(delim, end)) != std::string::npos)
			{
				end = message.find(delim, start);
				splitString.push_back(message.substr(start, end - start));
			}

			//Y rotation
			mEcsManager->TransformComp(ID)->transform *= RotationMatrixAxis(DegreesToRadians(std::stof(splitString[1]) * 10.0f) * mSceneManager->DeltaTime(), Vector4(0, 1, 0, 1));

			//X rotation
			mEcsManager->TransformComp(ID)->transform *= RotationMatrixAxis(DegreesToRadians(std::stof(splitString[2]) * 10.0f) * mSceneManager->DeltaTime(), Vector4(1, 0, 0, 1));
		}

		//Roll left
		if (message[0] == 'E' && message[1] != 'C')
		{
			int ID = static_cast<int>(message[1]) - 48;
			int ID2 = static_cast<int>(message[2]) - 48;

			mEcsManager->TransformComp(ID)->transform *= RotationMatrixAxis(DegreesToRadians(2 * -10.0f) * mSceneManager->DeltaTime(), Vector4(0, 0, 1, 1));
			RotateAroundPoint(ID2, Vector4(0, 0, 1, 0), Vector4(0, -40, 75, 0), 2 * -10.0f);
		}

		//Roll cam left
		if (message[0] == 'E' && message[1] == 'C')
		{
			int ID = static_cast<int>(message[2]) - 48;

			mEcsManager->TransformComp(ID)->transform *= RotationMatrixAxis(DegreesToRadians(2 * -10.0f) * mSceneManager->DeltaTime(), Vector4(0, 0, 1, 1));
		}

		//Roll right
		if (message[0] == 'Q' && message[1] != 'C')
		{
			int ID = static_cast<int>(message[1]) - 48;
			int ID2 = static_cast<int>(message[2]) - 48;

			mEcsManager->TransformComp(ID)->transform *= RotationMatrixAxis(DegreesToRadians(2 * 10.0f) * mSceneManager->DeltaTime(), Vector4(0, 0, 1, 1));
			RotateAroundPoint(ID2, Vector4(0, 0, 1, 0), Vector4(0, -40, 75, 0), 2 * 10.0f);
		}

		//Roll cam right
		if (message[0] == 'Q' && message[1] == 'C')
		{
			int ID = static_cast<int>(message[2]) - 48;

			mEcsManager->TransformComp(ID)->transform *= RotationMatrixAxis(DegreesToRadians(2 * 10.0f) * mSceneManager->DeltaTime(), Vector4(0, 0, 1, 1));
		}

		//Player jump message
		if (message[0] == 'J')
		{
			int ID = static_cast<int>(message[1]) - 48;
			int ID2 = static_cast<int>(message[2]) - 48;

			mEcsManager->VelocityComp(ID)->velocity += Vector4(0, 1, 0, 0) * 20.0f;
			mEcsManager->VelocityComp(ID2)->velocity += Vector4(0, 1, 0, 0) * 20.0f;
		}

		//Ship fire message
		if (message[0] == 'Z')
		{
			int ID = static_cast<int>(message[1]) - 48;
			int ID2 = static_cast<int>(message[2]) - 48;

			//Set spawn location and calculate firing direction
			Vector4 leftLaser = mEcsManager->TransformComp(ID)->translation + ((mEcsManager->TransformComp(ID)->right * -23) + (mEcsManager->TransformComp(ID)->up * 5));
			Vector4 directionLeft = leftLaser - Vector4(mEcsManager->TransformComp(ID2)->translation + mEcsManager->TransformComp(ID2)->forward * 300);

			int laser = EntitySpawner::SpawnLaser(leftLaser, Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 1), Vector4(1, 0, 0, 1), directionLeft * -40, 120,
				2, CustomCollisionMask::SHIP_LASER, CustomCollisionMask::SHIP_LASER | CustomCollisionMask::SHIP, 50, L"laser.wav");

			mNewBullets.push(laser);

			//Set spawn location and calculate firing direction
			Vector4 rightLaser = mEcsManager->TransformComp(ID)->translation + ((mEcsManager->TransformComp(ID)->right * 23) + (mEcsManager->TransformComp(ID)->up * 5));
			Vector4 directionRight = rightLaser - Vector4(mEcsManager->TransformComp(ID2)->translation + mEcsManager->TransformComp(ID2)->forward * 300);

			laser = EntitySpawner::SpawnLaser(rightLaser, Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 1), Vector4(1, 0, 0, 1), directionRight * -40, 120,
				2, CustomCollisionMask::SHIP_LASER, CustomCollisionMask::SHIP_LASER | CustomCollisionMask::SHIP, 50, L"laser.wav");

			mNewBullets.push(laser);
		}

		//Player fire message
		if (message[0] == 'X')
		{
			int ID = static_cast<int>(message[1]) - 48;
			int ID2 = static_cast<int>(message[2]) - 48;

			//Set spawn location and calculate firing direction
			Vector4 gunBarrel = mEcsManager->TransformComp(ID)->translation + (mEcsManager->TransformComp(ID)->forward * -2);
			Vector4 direction = gunBarrel - Vector4(mEcsManager->TransformComp(ID2)->translation + mEcsManager->TransformComp(ID2)->forward * 25);

			int laser = EntitySpawner::SpawnLaser(gunBarrel, Vector4(0.1f, 0.1f, 0.1f, 1), Vector4(0, 0, 0, 1), Vector4(1, 0, 0, 1), direction * -40, 120,
				2, CustomCollisionMask::GUN_LASER, CustomCollisionMask::GUN_LASER | CustomCollisionMask::PLAYER, 50, L"laser.wav");

			mNewBullets.push(laser);
		}

		//Gravity asteroid message
		if (message[0] == 'G')
		{
			//Split the message up on the delimiter
			std::vector<std::string> splitString;
			size_t start;
			size_t end = 0;
			const char delim = ':';

			while ((start = message.find_first_not_of(delim, end)) != std::string::npos)
			{
				end = message.find(delim, start);
				splitString.push_back(message.substr(start, end - start));
			}

			mEcsManager->AddGravityComp(Gravity{}, std::stoi(splitString[1]));
			mEcsManager->AddGravityComp(Gravity{}, std::stoi(splitString[2]));
		}

		//Freeze player message
		if (message[0] == 'F' && message[1] == 'Z')
		{
			int ID = static_cast<int>(message[2]) - 48;

			mEcsManager->VelocityComp(ID)->velocity = Vector4(0, 0, 0, 1);
			mEcsManager->VelocityComp(ID)->acceleration = Vector4(0, 0, 0, 1);
		}

		messages.pop();
	}
}

const int GameNetworking::PlayerNumber()
{
	return mPlayerNumber;
}

std::queue<int>& GameNetworking::NewBullets()
{
	return mNewBullets;
}

