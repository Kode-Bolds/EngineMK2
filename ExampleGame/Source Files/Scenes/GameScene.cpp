#include "GameScene.h"

using namespace KodeboldsMath;
using namespace EntitySpawner;

/// <summary>
/// Movement logic in the game
/// </summary>
void GameScene::Movement()
{
	//Forward movement
	if (mInputManager->KeyDown(KEYS::KEY_W))
	{
		//If ship cam is active, move ship
		if (mEcsManager->CameraComp(mActivePlayerShipCam)->active)
		{
			mEcsManager->VelocityComp(mActivePlayerShip)->acceleration += Vector4(0, 0, 1, 0) * mShipSpeed;
			mEcsManager->VelocityComp(mActivePlayerShipCam)->acceleration += Vector4(0, 0, 1, 0) * mShipSpeed;

			mNetworkManager->AddMessage("F" + std::to_string(mActivePlayerShip));
			mNetworkManager->AddMessage("F" + std::to_string(mActivePlayerShipCam));
		}
		//If player cam is active, move player cam
		if (mEcsManager->CameraComp(mActivePlayer)->active)
		{
			mEcsManager->VelocityComp(mActivePlayer)->acceleration += Vector4(0, 0, 1, 0) * mPlayerSpeed;
			mEcsManager->VelocityComp(mActivePlayerGun)->acceleration += Vector4(0, 0, -1, 0) * mPlayerSpeed;

			mNetworkManager->AddMessage("F" + std::to_string(mActivePlayer));
			mNetworkManager->AddMessage("B" + std::to_string(mActivePlayerGun));
		}
		//If free cam is active, move free cam
		if (mEcsManager->CameraComp(mActiveCamera)->active)
		{
			mEcsManager->VelocityComp(mActiveCamera)->acceleration += Vector4(0, 0, 1, 0) * mCameraSpeed;

			mNetworkManager->AddMessage("F" + std::to_string(mActiveCamera));
		}
	}
	else if (mInputManager->KeyUp(KEYS::KEY_W))
	{
		//If ship cam is active, move ship
		if (mEcsManager->CameraComp(mActivePlayerShipCam)->active)
		{
			mEcsManager->VelocityComp(mActivePlayerShip)->acceleration -= Vector4(0, 0, 1, 0) * mShipSpeed;
			mEcsManager->VelocityComp(mActivePlayerShipCam)->acceleration -= Vector4(0, 0, 1, 0) * mShipSpeed;

			mNetworkManager->AddMessage("FR" + std::to_string(mActivePlayerShip));
			mNetworkManager->AddMessage("FR" + std::to_string(mActivePlayerShipCam));
		}
		//If player cam is active, move player cam
		if (mEcsManager->CameraComp(mActivePlayer)->active)
		{
			mEcsManager->VelocityComp(mActivePlayer)->acceleration -= Vector4(0, 0, 1, 0) * mPlayerSpeed;
			mEcsManager->VelocityComp(mActivePlayerGun)->acceleration -= Vector4(0, 0, -1, 0) * mPlayerSpeed;

			mNetworkManager->AddMessage("FR" + std::to_string(mActivePlayer));
			mNetworkManager->AddMessage("BR" + std::to_string(mActivePlayerGun));
		}
		//If free cam is active, move free cam
		if (mEcsManager->CameraComp(mActiveCamera)->active)
		{
			mEcsManager->VelocityComp(mActiveCamera)->acceleration -= Vector4(0, 0, 1, 0) * mCameraSpeed;

			mNetworkManager->AddMessage("FR" + std::to_string(mActiveCamera));
		}
	}

	//Backwards movement
	if (mInputManager->KeyDown(KEYS::KEY_S))
	{
		//If ship cam is active, move ship
		if (mEcsManager->CameraComp(mActivePlayerShipCam)->active)
		{
			mEcsManager->VelocityComp(mActivePlayerShip)->acceleration += Vector4(0, 0, 1, 0) * -mShipSpeed;
			mEcsManager->VelocityComp(mActivePlayerShipCam)->acceleration += Vector4(0, 0, 1, 0) * -mShipSpeed;

			mNetworkManager->AddMessage("B" + std::to_string(mActivePlayerShip));
			mNetworkManager->AddMessage("B" + std::to_string(mActivePlayerShipCam));
		}
		//If player cam is active, move player cam
		if (mEcsManager->CameraComp(mActivePlayer)->active)
		{
			mEcsManager->VelocityComp(mActivePlayer)->acceleration += Vector4(0, 0, 1, 0) * -mPlayerSpeed;
			mEcsManager->VelocityComp(mActivePlayerGun)->acceleration += Vector4(0, 0, -1, 0) * -mPlayerSpeed;

			mNetworkManager->AddMessage("B" + std::to_string(mActivePlayer));
			mNetworkManager->AddMessage("F" + std::to_string(mActivePlayerGun));
		}
		//If free cam is active, move free cam
		if (mEcsManager->CameraComp(mActiveCamera)->active)
		{
			mEcsManager->VelocityComp(mActiveCamera)->acceleration += Vector4(0, 0, 1, 0) * -mCameraSpeed;

			mNetworkManager->AddMessage("B" + std::to_string(mActiveCamera));
		}
	}
	else if (mInputManager->KeyUp(KEYS::KEY_S))
	{
		//If ship cam is active, move ship
		if (mEcsManager->CameraComp(mActivePlayerShipCam)->active)
		{
			mEcsManager->VelocityComp(mActivePlayerShip)->acceleration -= Vector4(0, 0, 1, 0) * -mShipSpeed;
			mEcsManager->VelocityComp(mActivePlayerShipCam)->acceleration -= Vector4(0, 0, 1, 0) * -mShipSpeed;

			mNetworkManager->AddMessage("BR" + std::to_string(mActivePlayerShip));
			mNetworkManager->AddMessage("BR" + std::to_string(mActivePlayerShipCam));
		}
		//If player cam is active, move player cam
		if (mEcsManager->CameraComp(mActivePlayer)->active)
		{
			mEcsManager->VelocityComp(mActivePlayer)->acceleration -= Vector4(0, 0, 1, 0) * -mPlayerSpeed;
			mEcsManager->VelocityComp(mActivePlayerGun)->acceleration -= Vector4(0, 0, -1, 0) * -mPlayerSpeed;

			mNetworkManager->AddMessage("BR" + std::to_string(mActivePlayer));
			mNetworkManager->AddMessage("FR" + std::to_string(mActivePlayerGun));
		}
		//If free cam is active, move free cam
		if (mEcsManager->CameraComp(mActiveCamera)->active)
		{
			mEcsManager->VelocityComp(mActiveCamera)->acceleration -= Vector4(0, 0, 1, 0) * -mCameraSpeed;

			mNetworkManager->AddMessage("BR" + std::to_string(mActiveCamera));
		}
	}

	//Left movement
	if (mInputManager->KeyDown(KEYS::KEY_A))
	{
		//If ship cam is active, move ship
		if (mEcsManager->CameraComp(mActivePlayerShipCam)->active)
		{
			mEcsManager->VelocityComp(mActivePlayerShip)->acceleration += Vector4(1, 0, 0, 0) * -mShipSpeed;
			mEcsManager->VelocityComp(mActivePlayerShipCam)->acceleration += Vector4(1, 0, 0, 0) * -mShipSpeed;

			mNetworkManager->AddMessage("L" + std::to_string(mActivePlayerShip));
			mNetworkManager->AddMessage("L" + std::to_string(mActivePlayerShipCam));
		}
		//If player cam is active, move player cam
		if (mEcsManager->CameraComp(mActivePlayer)->active)
		{
			mEcsManager->VelocityComp(mActivePlayer)->acceleration += Vector4(1, 0, 0, 0) * -mPlayerSpeed;
			mEcsManager->VelocityComp(mActivePlayerGun)->acceleration += Vector4(-1, 0, 0, 0) * -mPlayerSpeed;

			mNetworkManager->AddMessage("L" + std::to_string(mActivePlayer));
			mNetworkManager->AddMessage("R" + std::to_string(mActivePlayerGun));
		}
		//If free cam is active, move free cam
		if (mEcsManager->CameraComp(mActiveCamera)->active)
		{
			mEcsManager->VelocityComp(mActiveCamera)->acceleration += Vector4(1, 0, 0, 0) * -mCameraSpeed;

			mNetworkManager->AddMessage("L" + std::to_string(mActiveCamera));
		}
	}
	else if (mInputManager->KeyUp(KEYS::KEY_A))
	{
		//If ship cam is active, move ship
		if (mEcsManager->CameraComp(mActivePlayerShipCam)->active)
		{
			mEcsManager->VelocityComp(mActivePlayerShip)->acceleration -= Vector4(1, 0, 0, 0) * -mShipSpeed;
			mEcsManager->VelocityComp(mActivePlayerShipCam)->acceleration -= Vector4(1, 0, 0, 0) * -mShipSpeed;

			mNetworkManager->AddMessage("LR" + std::to_string(mActivePlayerShip));
			mNetworkManager->AddMessage("LR" + std::to_string(mActivePlayerShipCam));
		}
		//If player cam is active, move player cam
		if (mEcsManager->CameraComp(mActivePlayer)->active)
		{
			mEcsManager->VelocityComp(mActivePlayer)->acceleration -= Vector4(1, 0, 0, 0) * -mPlayerSpeed;
			mEcsManager->VelocityComp(mActivePlayerGun)->acceleration -= Vector4(-1, 0, 0, 0) * -mPlayerSpeed;

			mNetworkManager->AddMessage("LR" + std::to_string(mActivePlayer));
			mNetworkManager->AddMessage("RR" + std::to_string(mActivePlayerGun));
		}
		//If free cam is active, move free cam
		if (mEcsManager->CameraComp(mActiveCamera)->active)
		{
			mEcsManager->VelocityComp(mActiveCamera)->acceleration -= Vector4(1, 0, 0, 0) * -mCameraSpeed;

			mNetworkManager->AddMessage("LR" + std::to_string(mActiveCamera));
		}
	}

	//Right movement
	if (mInputManager->KeyDown(KEYS::KEY_D))
	{
		//If ship cam is active, move ship
		if (mEcsManager->CameraComp(mActivePlayerShipCam)->active)
		{
			mEcsManager->VelocityComp(mActivePlayerShip)->acceleration += Vector4(1, 0, 0, 0) * mShipSpeed;
			mEcsManager->VelocityComp(mActivePlayerShipCam)->acceleration += Vector4(1, 0, 0, 0) * mShipSpeed;

			mNetworkManager->AddMessage("R" + std::to_string(mActivePlayerShip));
			mNetworkManager->AddMessage("R" + std::to_string(mActivePlayerShipCam));
		}
		//If player cam is active, move player cam
		if (mEcsManager->CameraComp(mActivePlayer)->active)
		{
			mEcsManager->VelocityComp(mActivePlayer)->acceleration += Vector4(1, 0, 0, 0) * mPlayerSpeed;
			mEcsManager->VelocityComp(mActivePlayerGun)->acceleration += Vector4(-1, 0, 0, 0) * mPlayerSpeed;

			mNetworkManager->AddMessage("R" + std::to_string(mActivePlayer));
			mNetworkManager->AddMessage("L" + std::to_string(mActivePlayerGun));
		}
		//If free cam is active, move free cam
		if (mEcsManager->CameraComp(mActiveCamera)->active)
		{
			mEcsManager->VelocityComp(mActiveCamera)->acceleration += Vector4(1, 0, 0, 0) * mCameraSpeed;

			mNetworkManager->AddMessage("R" + std::to_string(mActiveCamera));
		}
	}
	else if (mInputManager->KeyUp(KEYS::KEY_D))
	{
		//If ship cam is active, move ship
		if (mEcsManager->CameraComp(mActivePlayerShipCam)->active)
		{
			mEcsManager->VelocityComp(mActivePlayerShip)->acceleration -= Vector4(1, 0, 0, 0) * mShipSpeed;
			mEcsManager->VelocityComp(mActivePlayerShipCam)->acceleration -= Vector4(1, 0, 0, 0) * mShipSpeed;

			mNetworkManager->AddMessage("RR" + std::to_string(mActivePlayerShip));
			mNetworkManager->AddMessage("RR" + std::to_string(mActivePlayerShipCam));
		}
		//If player cam is active, move player cam
		if (mEcsManager->CameraComp(mActivePlayer)->active)
		{
			mEcsManager->VelocityComp(mActivePlayer)->acceleration -= Vector4(1, 0, 0, 0) * mPlayerSpeed;
			mEcsManager->VelocityComp(mActivePlayerGun)->acceleration -= Vector4(-1, 0, 0, 0) * mPlayerSpeed;

			mNetworkManager->AddMessage("RR" + std::to_string(mActivePlayer));
			mNetworkManager->AddMessage("LR" + std::to_string(mActivePlayerGun));
		}
		//If free cam is active, move free cam
		if (mEcsManager->CameraComp(mActiveCamera)->active)
		{
			mEcsManager->VelocityComp(mActiveCamera)->acceleration -= Vector4(1, 0, 0, 0) * mCameraSpeed;

			mNetworkManager->AddMessage("RR" + std::to_string(mActiveCamera));
		}
	}

	//Up movement
	if (mInputManager->KeyDown(KEYS::KEY_SPACE))
	{
		//If ship cam is active, move ship
		if (mEcsManager->CameraComp(mActivePlayerShipCam)->active)
		{
			mEcsManager->VelocityComp(mActivePlayerShip)->acceleration += Vector4(0, 1, 0, 0) * mShipSpeed;
			mEcsManager->VelocityComp(mActivePlayerShipCam)->acceleration += Vector4(0, 1, 0, 0) * mShipSpeed;

			mNetworkManager->AddMessage("U" + std::to_string(mActivePlayerShip));
			mNetworkManager->AddMessage("U" + std::to_string(mActivePlayerShipCam));
		}
		//If player cam is active, move player cam
		if (mEcsManager->CameraComp(mActivePlayer)->active && mPlayerIsGrounded)
		{
			mEcsManager->VelocityComp(mActivePlayer)->velocity += Vector4(0, 1, 0, 0) * mPlayerJumpSpeed;
			mEcsManager->VelocityComp(mActivePlayerGun)->velocity += Vector4(0, 1, 0, 0) * mPlayerJumpSpeed;

			mNetworkManager->AddMessage("J" + std::to_string(mActivePlayer) + std::to_string(mActivePlayerGun));
		}
		//If free cam is active, move free cam
		if (mEcsManager->CameraComp(mActiveCamera)->active)
		{
			mEcsManager->VelocityComp(mActiveCamera)->acceleration += Vector4(0, 1, 0, 0) * mCameraSpeed;

			mNetworkManager->AddMessage("U" + std::to_string(mActivePlayerShip));
			mNetworkManager->AddMessage("U" + std::to_string(mActivePlayerShipCam));
		}
	}
	else if (mInputManager->KeyUp(KEYS::KEY_SPACE))
	{
		//If ship cam is active, move ship
		if (mEcsManager->CameraComp(mActivePlayerShipCam)->active)
		{
			mEcsManager->VelocityComp(mActivePlayerShip)->acceleration -= Vector4(0, 1, 0, 0) * mShipSpeed;
			mEcsManager->VelocityComp(mActivePlayerShipCam)->acceleration -= Vector4(0, 1, 0, 0) * mShipSpeed;

			mNetworkManager->AddMessage("UR" + std::to_string(mActivePlayerShip));
			mNetworkManager->AddMessage("UR" + std::to_string(mActivePlayerShipCam));
		}
		//If free cam is active, move free cam
		if (mEcsManager->CameraComp(mActiveCamera)->active)
		{
			mEcsManager->VelocityComp(mActiveCamera)->acceleration -= Vector4(0, 1, 0, 0) * mCameraSpeed;

			mNetworkManager->AddMessage("UR" + std::to_string(mActiveCamera));
		}
	}

	//Down movement
	if (mInputManager->KeyDown(KEYS::KEY_LEFT_CTRL))
	{
		//If ship cam is active, move ship
		if (mEcsManager->CameraComp(mActivePlayerShipCam)->active)
		{
			mEcsManager->VelocityComp(mActivePlayerShip)->acceleration += Vector4(0, 1, 0, 0) * -mShipSpeed;
			mEcsManager->VelocityComp(mActivePlayerShipCam)->acceleration += Vector4(0, 1, 0, 0) * -mShipSpeed;

			mNetworkManager->AddMessage("D" + std::to_string(mActivePlayerShip));
			mNetworkManager->AddMessage("D" + std::to_string(mActivePlayerShipCam));
		}
		//If free cam is active, move free cam
		if (mEcsManager->CameraComp(mActiveCamera)->active)
		{
			mEcsManager->VelocityComp(mActiveCamera)->acceleration += Vector4(0, 1, 0, 0) * -mCameraSpeed;

			mNetworkManager->AddMessage("D" + std::to_string(mActiveCamera));
		}
	}
	else if (mInputManager->KeyUp(KEYS::KEY_LEFT_CTRL))
	{
		//If ship cam is active, move ship
		if (mEcsManager->CameraComp(mActivePlayerShipCam)->active)
		{
			mEcsManager->VelocityComp(mActivePlayerShip)->acceleration -= Vector4(0, 1, 0, 0) * -mShipSpeed;
			mEcsManager->VelocityComp(mActivePlayerShipCam)->acceleration -= Vector4(0, 1, 0, 0) * -mShipSpeed;

			mNetworkManager->AddMessage("DR" + std::to_string(mActivePlayerShip));
			mNetworkManager->AddMessage("DR" + std::to_string(mActivePlayerShipCam));
		}
		//If free cam is active, move free cam
		if (mEcsManager->CameraComp(mActiveCamera)->active)
		{
			mEcsManager->VelocityComp(mActiveCamera)->acceleration -= Vector4(0, 1, 0, 0) * -mCameraSpeed;

			mNetworkManager->AddMessage("DR" + std::to_string(mActiveCamera));
		}
	}

	//Freeze currently active camera, removing all velocity and acceleration
	if (mInputManager->KeyDown(KEYS::KEY_LEFT_SHIFT))
	{
		//If ship cam is active, freeze ship
		if (mEcsManager->CameraComp(mActivePlayerShipCam)->active)
		{
			mEcsManager->VelocityComp(mActivePlayerShip)->velocity = Vector4(0, 0, 0, 1);
			mEcsManager->VelocityComp(mActivePlayerShipCam)->velocity = Vector4(0, 0, 0, 1);
			mEcsManager->VelocityComp(mActivePlayerShip)->acceleration = Vector4(0, 0, 0, 1);
			mEcsManager->VelocityComp(mActivePlayerShipCam)->acceleration = Vector4(0, 0, 0, 1);

			mNetworkManager->AddMessage("FZ" + std::to_string(mActivePlayerShip));
			mNetworkManager->AddMessage("FZ" + std::to_string(mActivePlayerShipCam));
		}
		//If player cam is active, freeze player cam
		if (mEcsManager->CameraComp(mActivePlayer)->active)
		{
			mEcsManager->VelocityComp(mActivePlayer)->velocity = Vector4(0, 0, 0, 1);
			mEcsManager->VelocityComp(mActivePlayerGun)->velocity = Vector4(0, 0, 0, 1);
			mEcsManager->VelocityComp(mActivePlayer)->acceleration = Vector4(0, 0, 0, 1);
			mEcsManager->VelocityComp(mActivePlayerGun)->acceleration = Vector4(0, 0, 0, 1);

			mNetworkManager->AddMessage("FZ" + std::to_string(mActivePlayer));
			mNetworkManager->AddMessage("FZ" + std::to_string(mActivePlayerGun));
		}
		//If free cam is active, freeze free cam
		if (mEcsManager->CameraComp(mActiveCamera)->active)
		{
			mEcsManager->VelocityComp(mActiveCamera)->velocity = Vector4(0, 0, 0, 1);
			mEcsManager->VelocityComp(mActiveCamera)->acceleration = Vector4(0, 0, 0, 1);

			mNetworkManager->AddMessage("FZ" + std::to_string(mActiveCamera));
		}
	}
}

/// <summary>
/// Rotation logic in the game
/// </summary>
void GameScene::Rotation()
{
	float deltaX = mInputManager->MousePos().X;
	float deltaY = mInputManager->MousePos().Y;

	//If mouse moved
	if (deltaX != 0 || deltaY != 0)
	{

		//If ship cam is active, rotate ship
		if (mEcsManager->CameraComp(mActivePlayerShipCam)->active)
		{
			//Y rotation
			mEcsManager->TransformComp(mActivePlayerShip)->transform *= RotationMatrixAxis(DegreesToRadians(deltaX * mRotationSpeed) * mSceneManager->DeltaTime(), Vector4(0, 1, 0, 1));
			RotateAroundPoint(mActivePlayerShipCam, Vector4(0, 1, 0, 0), Vector4(0, -40, 75, 0), deltaX * mRotationSpeed);

			//X rotation
			mEcsManager->TransformComp(mActivePlayerShip)->transform *= RotationMatrixAxis(DegreesToRadians(deltaY * mRotationSpeed) * mSceneManager->DeltaTime(), Vector4(1, 0, 0, 1));
			RotateAroundPoint(mActivePlayerShipCam, Vector4(1, 0, 0, 0), Vector4(0, -40, 75, 0), deltaY * mRotationSpeed);

			mNetworkManager->AddMessage("SR" + std::to_string(mActivePlayerShip) + std::to_string(mActivePlayerShipCam) + ":" + std::to_string(deltaX) + ":" + std::to_string(deltaY));
		}
		//If player cam is active, rotate player
		if (mEcsManager->CameraComp(mPlayer)->active)
		{
			//Y rotation
			mEcsManager->TransformComp(mActivePlayer)->transform *= RotationMatrixAxis(DegreesToRadians(deltaX * mRotationSpeed) * mSceneManager->DeltaTime(), Vector4(0, 1, 0, 1));
			RotateAroundPoint(mActivePlayerGun, Vector4(0, 1, 0, 0), Vector4(1, -1, 2.0f, 0), deltaX * mRotationSpeed);

			mNetworkManager->AddMessage("PR" + std::to_string(mActivePlayer) + std::to_string(mActivePlayerGun) + ":" + std::to_string(deltaX));
		}
		//If free cam is active, rotate free cam
		if (mEcsManager->CameraComp(mActiveCamera)->active)
		{
			//Y rotation
			mEcsManager->TransformComp(mActiveCamera)->transform *= RotationMatrixAxis(DegreesToRadians(deltaX * mRotationSpeed) * mSceneManager->DeltaTime(), Vector4(0, 1, 0, 1));

			//X rotation
			mEcsManager->TransformComp(mActiveCamera)->transform *= RotationMatrixAxis(DegreesToRadians(deltaY * mRotationSpeed) * mSceneManager->DeltaTime(), Vector4(1, 0, 0, 1));

			mNetworkManager->AddMessage("N" + std::to_string(mActiveCamera) + ":" + std::to_string(deltaX) + ":" + std::to_string(deltaY));
		}
	}

	//Roll rotation
	//If ship cam is active, rotate ship
	if (mEcsManager->CameraComp(mActivePlayerShipCam)->active)
	{
		//Right roll
		if (mInputManager->KeyHeld(KEYS::KEY_Q))
		{
			mEcsManager->TransformComp(mActivePlayerShip)->transform *= RotationMatrixAxis(DegreesToRadians(2 * mRotationSpeed) * mSceneManager->DeltaTime(), Vector4(0, 0, 1, 1));
			RotateAroundPoint(mActivePlayerShipCam, Vector4(0, 0, 1, 0), Vector4(0, -40, 75, 0), 2 * mRotationSpeed);

			mNetworkManager->AddMessage("Q" + std::to_string(mActivePlayerShip) + std::to_string(mActivePlayerShipCam));
		}
		//Left roll
		if (mInputManager->KeyHeld(KEYS::KEY_E))
		{
			mEcsManager->TransformComp(mActivePlayerShip)->transform *= RotationMatrixAxis(DegreesToRadians(2 * -mRotationSpeed) * mSceneManager->DeltaTime(), Vector4(0, 0, 1, 1));
			RotateAroundPoint(mActivePlayerShipCam, Vector4(0, 0, 1, 0), Vector4(0, -40, 75, 0), 2 * -mRotationSpeed);

			mNetworkManager->AddMessage("E" + std::to_string(mActivePlayerShip) + std::to_string(mActivePlayerShipCam));
		}
	}
	//If free cam is active, rotate free cam
	if (mEcsManager->CameraComp(mActiveCamera)->active)
	{
		//Right roll
		if (mInputManager->KeyHeld(KEYS::KEY_Q))
		{
			mEcsManager->TransformComp(mActiveCamera)->transform *= RotationMatrixAxis(DegreesToRadians(2 * mRotationSpeed) * mSceneManager->DeltaTime(), Vector4(0, 0, 1, 1));

			mNetworkManager->AddMessage("QC" + std::to_string(mActivePlayerShip));
		}
		//Left roll
		if (mInputManager->KeyHeld(KEYS::KEY_E))
		{
			mEcsManager->TransformComp(mActiveCamera)->transform *= RotationMatrixAxis(DegreesToRadians(2 * -mRotationSpeed) * mSceneManager->DeltaTime(), Vector4(0, 0, 1, 1));

			mNetworkManager->AddMessage("EC" + std::to_string(mActivePlayerShip));
		}
	}
}

/// <summary>
/// Shooting logic in the game
/// </summary>
void GameScene::Shooting()
{
	mTimeSinceLastFire += mSceneManager->DeltaTime();

	//Fire on left click
	if (mInputManager->KeyDown(KEYS::MOUSE_BUTTON_LEFT) && mTimeSinceLastFire > mRateOfFire)
	{
		//If ship cam is active, fire ship lasers
		if (mEcsManager->CameraComp(mActivePlayerShipCam)->active)
		{
			//Set spawn location and calculate firing direction
			Vector4 leftLaser = mEcsManager->TransformComp(mActivePlayerShip)->translation + ((mEcsManager->TransformComp(mActivePlayerShip)->right * -23) + (mEcsManager->TransformComp(mActivePlayerShip)->up * 5));
			Vector4 directionLeft = leftLaser - Vector4(mEcsManager->TransformComp(mActivePlayerShipCam)->translation + mEcsManager->TransformComp(mActivePlayerShipCam)->forward * 300);

			int laser = SpawnLaser(leftLaser, Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 1), Vector4(1, 0, 0, 1), directionLeft * -40, 120,
				2, CustomCollisionMask::SHIP_LASER, CustomCollisionMask::SHIP_LASER | CustomCollisionMask::SHIP, 50, L"laser.wav");

			//Add laser to life timer list
			mBulletLifeTimers.push_back(std::make_pair(laser, 0.0f));

			//Set spawn location and calculate firing direction
			Vector4 rightLaser = mEcsManager->TransformComp(mActivePlayerShip)->translation + ((mEcsManager->TransformComp(mActivePlayerShip)->right * 23) + (mEcsManager->TransformComp(mActivePlayerShip)->up * 5));
			Vector4 directionRight = rightLaser - Vector4(mEcsManager->TransformComp(mActivePlayerShipCam)->translation + mEcsManager->TransformComp(mActivePlayerShipCam)->forward * 300);

			laser = SpawnLaser(rightLaser, Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 1), Vector4(1, 0, 0, 1), directionRight * -40, 120,
				2, CustomCollisionMask::SHIP_LASER, CustomCollisionMask::SHIP_LASER | CustomCollisionMask::SHIP, 50, L"laser.wav");

			//Add laser to life timer list
			mBulletLifeTimers.push_back(std::make_pair(laser, 0.0f));
			mTimeSinceLastFire = 0;

			mNetworkManager->AddMessage("Z" + std::to_string(mActivePlayerShip) + std::to_string(mActivePlayerShipCam));
		}

		//If player cam is active, fire gun
		if (mEcsManager->CameraComp(mActivePlayer)->active)
		{
			//Set spawn location and calculate firing direction
			Vector4 gunBarrel = mEcsManager->TransformComp(mActivePlayerGun)->translation + (mEcsManager->TransformComp(mActivePlayerGun)->forward * -2);
			Vector4 direction = gunBarrel - Vector4(mEcsManager->TransformComp(mActivePlayer)->translation + mEcsManager->TransformComp(mActivePlayer)->forward * 25);

			int laser = SpawnLaser(gunBarrel, Vector4(0.1f, 0.1f, 0.1f, 1), Vector4(0, 0, 0, 1), Vector4(1, 0, 0, 1), direction * -40, 120,
				2, CustomCollisionMask::GUN_LASER, CustomCollisionMask::GUN_LASER | CustomCollisionMask::PLAYER, 50, L"laser.wav");

			//Add laser to life timer list
			mBulletLifeTimers.push_back(std::make_pair(laser, 0.0f));
			mTimeSinceLastFire = 0;

			mNetworkManager->AddMessage("X" + std::to_string(mActivePlayerGun) + std::to_string(mActivePlayer));
		}
	}

	//Update timer for each bullet
	for (auto& bullet : mBulletLifeTimers)
	{
		bullet.second += mSceneManager->DeltaTime();

		//Destroy bullet if it's lifetime is greater than the limit
		if (bullet.second >= 2)
		{
			mEcsManager->DestroyEntity(bullet.first);
			mBulletLifeTimers.erase(std::remove_if(mBulletLifeTimers.begin(), mBulletLifeTimers.end(), [&](const auto& pBullet) {return pBullet.first == bullet.first; }), mBulletLifeTimers.end());
		}
	}
}

/// <summary>
/// Rotates an object around a point in space
/// </summary>
/// <param name="pAxis">Axis of rotation</param>
/// <param name="pPoint">Point to rotate around</param>
/// <param name="pAngle">Angle of rotation</param>
void GameScene::RotateAroundPoint(const int pEntity, const KodeboldsMath::Vector4 & pAxis, const KodeboldsMath::Vector4 & pPoint, const float& pAngle)
{
	const float angleInRadians = DegreesToRadians(pAngle);

	auto translateTo = TranslationMatrix(pPoint);
	auto rotation = RotationMatrixAxis(angleInRadians * mSceneManager->DeltaTime(), pAxis);
	auto translateBack = TranslationMatrix(pPoint * -1);

	mEcsManager->TransformComp(pEntity)->transform *= translateTo * rotation * translateBack;
}

/// <summary>
/// On click logic for main menu button
/// </summary>
void GameScene::OnClick_MainMenuButton()
{
	mSceneManager->LoadScene<MenuScene>();
}

/// <summary>
/// On click logic for resume button
/// </summary>
void GameScene::OnClick_ResumeGameButton()
{
	OnUnPause();
}

/// <summary>
/// Default constructor
/// </summary>
GameScene::GameScene()
{
}

/// <summary>
/// Default destructor
/// </summary>
GameScene::~GameScene()
{
}

/// <summary>
/// Update loop for the scene
/// </summary>
void GameScene::Update()
{
	if (mGameState == GAME_STATE::PLAYING)
	{
		mGameNetworking.ProcessMessages();
		mPlayerNumber = mGameNetworking.PlayerNumber();

		if (mPlayerNumber == 2)
		{
			mEcsManager->CameraComp(mPlayerShipCam)->active = false;
			mEcsManager->CameraComp(mPlayerShipCam2)->active = true;
			mActiveCam = mPlayerShipCam2;

			mActivePlayer = mPlayer2;
			mActivePlayerGun = mPlayerGun2;
			mActivePlayerShip = mPlayerShip2;
			mActivePlayerShipCam = mPlayerShipCam2;
			mActivePlayerShipEngine = mPlayerShipEngine2;
			mActiveCamera = mCamera2;
		}

		int newBulletCount = mGameNetworking.NewBullets().size();

		for (int i = 0; i < newBulletCount; i++)
		{
			mBulletLifeTimers.push_back(std::make_pair(mGameNetworking.NewBullets().front(), 0.0f));
			mGameNetworking.NewBullets().pop();
		}

		Movement();
		Rotation();
		Shooting();

		//Rotate sun
		mEcsManager->TransformComp(mSun)->transform *= RotationMatrixY(DegreesToRadians(5) * mSceneManager->DeltaTime());

		//Switch between cameras
		//Ship
		if (mInputManager->KeyDown(KEYS::KEY_F1))
		{
			mEcsManager->CameraComp(mActivePlayerShipCam)->active = true;
			mEcsManager->CameraComp(mActivePlayer)->active = false;
			mEcsManager->CameraComp(mActiveCamera)->active = false;

			mActiveCam = mActivePlayerShipCam;
		}
		//Player
		if (mInputManager->KeyDown(KEYS::KEY_F2))
		{
			mEcsManager->CameraComp(mActivePlayerShipCam)->active = false;
			mEcsManager->CameraComp(mActivePlayer)->active = true;
			mEcsManager->CameraComp(mActiveCamera)->active = false;

			mActiveCam = mActivePlayer;
		}
		//Free cam
		if (mInputManager->KeyDown(KEYS::KEY_F3))
		{
			mEcsManager->CameraComp(mActivePlayerShipCam)->active = false;
			mEcsManager->CameraComp(mActivePlayer)->active = false;
			mEcsManager->CameraComp(mActiveCamera)->active = true;

			mActiveCam = mActiveCamera;
		}

		//If the player doesn't have a gravity component
		if (!mEcsManager->GravityComp(mPlayer))
		{
			//Check if the player is colliding with something, else add gravity
			if (mEcsManager->CollisionComp(mPlayer))
			{
				//If it's not the floor, player is not grounded, add gravity
				if (!(mEcsManager->CollisionComp(mPlayer)->collidedEntityCollisionMask == CustomCollisionMask::FLOOR))
				{
					mEcsManager->AddGravityComp(Gravity{}, mPlayer);
					mEcsManager->AddGravityComp(Gravity{}, mPlayerGun);
					mPlayerIsGrounded = false;
				}
				else
				{
					mPlayerIsGrounded = true;
				}
			}
			else
			{
				mEcsManager->AddGravityComp(Gravity{}, mPlayer);
				mEcsManager->AddGravityComp(Gravity{}, mPlayerGun);
				mPlayerIsGrounded = false;
			}
		}

		//If the player doesn't have a gravity component
		if (!mEcsManager->GravityComp(mPlayer2))
		{
			//Check if the player is colliding with something, else add gravity
			if (mEcsManager->CollisionComp(mPlayer2))
			{
				//If it's not the floor, player is not grounded, add gravity
				if (!(mEcsManager->CollisionComp(mPlayer2)->collidedEntityCollisionMask == CustomCollisionMask::FLOOR))
				{
					mEcsManager->AddGravityComp(Gravity{}, mPlayer2);
					mEcsManager->AddGravityComp(Gravity{}, mPlayerGun2);
					mPlayerIsGrounded2 = false;
				}
				else
				{
					mPlayerIsGrounded2 = true;
				}
			}
			else
			{
				mEcsManager->AddGravityComp(Gravity{}, mPlayer2);
				mEcsManager->AddGravityComp(Gravity{}, mPlayerGun2);
				mPlayerIsGrounded2 = false;
			}
		}

		//Add gravity to gravity asteroids
		if (mInputManager->KeyDown(KEYS::KEY_G))
		{
			mEcsManager->AddGravityComp(Gravity{}, mGravityAsteroid1);
			mEcsManager->AddGravityComp(Gravity{}, mGravityAsteroid2);

			mNetworkManager->AddMessage("G:" + std::to_string(mGravityAsteroid1) + ":" + std::to_string(mGravityAsteroid2));
		}

		// Turn On Pause Menu
		if (mInputManager->KeyDown(KEYS::KEY_ESC))
		{
			OnPause();
		}
	}
	else { // the game is now paused


		// Turn off Pause Menu
		if (mInputManager->KeyDown(KEYS::KEY_ESC))
		{
			OnUnPause();
		}
	}
}

/// <summary>
/// Scene setup on load
/// </summary>
void GameScene::OnLoad()
{
	//Clears GUI from previous scene
	resourceManager->mSprites.clear();
	resourceManager->mButtons.clear();
	mGUIManager->GetQuads()->clear();
	mGUIManager->GetTextVector()->clear();

	//Allows the user to use the mouse again as normal
	mInputManager->CenterCursor(true);

	//Spawn ship engine
	//Vector4 engineStartPos = mPlayerShipStartPos - Vector4(0, -10, 15, 1);
	//mPlayerShipEngine = SpawnEngine(engineStartPos, Vector4(10, 10, 10, 1), Vector4(0, 0, 0, 1), 4, L"", L"");

	//Spawn player ship
	mPlayerShipStartPos = Vector4(0, 30, -50, 1);
	mActivePlayerShip = mPlayerShip = SpawnShip(mPlayerShipStartPos, Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 0), 40, 50, CustomCollisionMask::SHIP,
		CustomCollisionMask::SHIP | CustomCollisionMask::SHIP_LASER | CustomCollisionMask::PLAYER, L"ship_diffuse.dds", L"ship_normal.dds");

	//Spawn player ship cam
	mActivePlayerShipCam = mPlayerShipCam = SpawnCamera(mPlayerShipStartPos + Vector4(0, 40, -75, 1), Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 0), 60, 1, 10000, 40);
	mEcsManager->CameraComp(mPlayerShipCam)->active = true;
	mActiveCam = mPlayerShipCam;

	//Spawn player
	mPlayerStartPos = Vector4(0, 50, -100, 1);
	mActivePlayer = mPlayer = SpawnPlayer(mPlayerStartPos, Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 0), 60, 1, 10000, 10, mPlayerStartPos.XYZ() - Vector3(1, 4, 1), mPlayerStartPos.XYZ() + Vector3(1, 2, 1),
		CustomCollisionMask::PLAYER, CustomCollisionMask::PLAYER | CustomCollisionMask::GUN_LASER | CustomCollisionMask::SHIP);

	//Spawn player gun model
	mActivePlayerGun = mPlayerGun = SpawnLaserGun(mPlayerStartPos + Vector4(1, -1, 2.0f, 0), Vector4(1, 1, 1, 1), Vector4(0, 3.14f, 0, 1), L"laser_gun_diffuse.dds", L"laser_gun_normal.dds", 10);
	mRateOfFire = 0.5f;

	//Spawn free cam
	mActiveCamera = mCamera = SpawnCamera(Vector4(5, 2, -100, 1), Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 0), 60, 1, 10000, 50);

	//Spawn player ship 2
	mPlayerShipStartPos2 = Vector4(50, 30, -50, 1);
	mPlayerShip2 = SpawnShip(mPlayerShipStartPos2, Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 0), 40, 50, CustomCollisionMask::SHIP,
		CustomCollisionMask::SHIP | CustomCollisionMask::SHIP_LASER | CustomCollisionMask::PLAYER, L"ship_diffuse.dds", L"ship_normal.dds");

	//Spawn player ship cam 2
	mPlayerShipCam2 = SpawnCamera(mPlayerShipStartPos2 + Vector4(0, 40, -75, 1), Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 0), 60, 1, 10000, 40);
	mEcsManager->CameraComp(mPlayerShipCam2)->active = false;

	//Spawn player 2
	mPlayerStartPos2 = Vector4(20, 50, -100, 1);
	mPlayer2 = SpawnPlayer(mPlayerStartPos2, Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 0), 60, 1, 10000, 10, mPlayerStartPos2.XYZ() - Vector3(1, 4, 1), mPlayerStartPos2.XYZ() + Vector3(1, 2, 1),
		CustomCollisionMask::PLAYER, CustomCollisionMask::PLAYER | CustomCollisionMask::GUN_LASER | CustomCollisionMask::SHIP);

	//Spawn player gun model 2
	mPlayerGun2 = SpawnLaserGun(mPlayerStartPos2 + Vector4(1, -1, 2.0f, 0), Vector4(1, 1, 1, 1), Vector4(0, 3.14f, 0, 1), L"laser_gun_diffuse.dds", L"laser_gun_normal.dds", 10);
	mRateOfFire = 0.5f;

	//Spawn free cam 2
	mCamera2 = SpawnCamera(Vector4(5, 2, -100, 1), Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 0), 60, 1, 10000, 50);

	//Set acceleration speeds
	mPlayerSpeed = 20.0f;
	mPlayerJumpSpeed = 20.0f;
	mShipSpeed = 20.0f;
	mCameraSpeed = 20.0f;
	mRotationSpeed = 10.0f;


	//Spawn planet surface
	SpawnPlanetSurface(Vector4(0, -100, -100, 1), Vector4(0.02f, 0.01f, 0.02f, 1), Vector4(0, 0, 0, 1), L"planet_diffuse.dds", L"planet_normal.dds");

	//Spawn sun
	mSun = SpawnSun(Vector4(0, 200, 2000, 1), Vector4(500, 500, 500, 1), Vector4(0, 0, 0, 1));

	//Spawn sun light
	mSunLight = mEcsManager->CreateEntity();
	DirectionalLight dl{ Vector4(0, 0.7f, 1, 1), Vector4(1.0f, 0.8f, 0.7f, 1) };
	mEcsManager->AddDirectionalLightComp(dl, mSunLight);

	Transform trans{};
	trans.translation = Vector4(0, 125, 500, 1);
	trans.scale = Vector4(1, 1, 1, 1);
	trans.rotation = Vector4(PI, 0, 0, 1);
	entitySpawnerEcsManager->AddTransformComp(trans, mSunLight);

	Camera cam{ 60, 1, 1500, std::vector<int>{0}, false };
	entitySpawnerEcsManager->AddCameraComp(cam, mSunLight);

	//Spawn shadow demo asteroid
	int asteroid = SpawnAsteroid(Vector4(0, -100, 100, 1), Vector4(3, 3, 3, 1), Vector4(0, 0, 0, 1), 10, 0,
		CustomCollisionMask::ASTEROID, L"asteroid_diffuse.dds", L"asteroid_normal.dds");

	//Spawn skybox
	SpawnSkyBox();

	//Spawn testing asteroid field
	for (int i = -200; i < 200; i += 40)
	{
		for (int j = -5; j < 5; j++)
		{
			for (int k = -400; k > -800; k -= 40)
			{
				SpawnAsteroid(Vector4(i, 40 * j, k, 1), Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 1), 10, 0, CustomCollisionMask::ASTEROID, L"asteroid_diffuse.dds", L"asteroid_normal.dds");
			}
		}
	}

	//Spawn gravity asteroids
	mGravityAsteroid1 = SpawnAsteroid(Vector4(100, 350, -600, 1), Vector4(5, 5, 5, 1), Vector4(0, 0, 0, 1), 50, 0, CustomCollisionMask::SHIP, L"asteroid_diffuse.dds", L"asteroid_normal.dds");
	mGravityAsteroid2 = SpawnAsteroid(Vector4(-100, 350, -600, 1), Vector4(5, 5, 5, 1), Vector4(0, 0, 0, 1), 50, 0, CustomCollisionMask::SHIP, L"asteroid_diffuse.dds", L"asteroid_normal.dds");

	//Spawn environment asteroid field
	for (int j = -2; j < 2; j++)
	{
		for (int i = 0; i < 360; i += 10)
		{
			int randScale = rand() % 6 + 2;
			int randRotation = rand() % 2 - 2;
			int asteroid = SpawnAsteroid(Vector4(0, 100 * j, -100, 1), Vector4(1, 1, 1, 1) * randScale, Vector4(0, DegreesToRadians(i + randRotation), 0, 1), 10 * randScale, 0,
				CustomCollisionMask::ASTEROID, L"asteroid_diffuse.dds", L"asteroid_normal.dds");

			//Translate outwards, then reverse rotation
			mEcsManager->TransformComp(asteroid)->transform *= TranslationMatrix(Vector4(0, 0, 300, 1));
			mEcsManager->TransformComp(asteroid)->transform *= RotationMatrixY(-DegreesToRadians(i + randRotation));
		}
	}



	//----------------------------------------------------------------------\\
	//EVERYTHING BELOW THIS POINT NEEDS TO BE TIDIED UP AND PUT IN FUNCTIONS\\
	//----------------------------------------------------------------------\\

	/*
	{
		int screenspaceQuad = mEcsManager->CreateEntity();
		Geometry geom{ L"cube.obj" };
		mEcsManager->AddGeometryComp(geom, screenspaceQuad);
		Shader shaderm{ L"distortionShader.fx" , BlendState::ALPHABLEND, CullState::NONE, DepthState::NONE, std::vector<int>(), false };
		//mEcsManager->AddShaderComp(shaderm, screenspaceQuad);
		Texture texturem{};
		texturem.diffuse = L"stones.DDS";
		texturem.normal = L"distortionTest.dds";
		mEcsManager->AddTextureComp(texturem, screenspaceQuad);

		Transform transCm{};
		transCm.scale = Vector4(10, 10, 10, 10);
		transCm.translation = Vector4(0, 0, 0, 1);

		mEcsManager->AddTransformComp(transCm, screenspaceQuad);
	}
	*/

	//------------ GUI ------------\\
	// Crosshair
	mCrosshair = mGUIManager->LoadSprite(L"crosshair.png", GUIManager::SpriteOrigin::CENTRE, GUIManager::SpritePosition::CENTRE_MIDDLE, Vector2(0, 0), 0, 0.045f, true);

	// SCORE
	mScoreLabelText = mGUIManager->Write(L"SCORE: ", GUIManager::TextOrigin::CENTRE, GUIManager::TextPosition::LEFT_BOTTOM, Vector2(130, -50), L"AlienEncounters.spritefont",
		0.0f, 0.75f, Vector4(1.0f, 0.0f, 0.0f, 1.0f), true);
	mScoreText = mGUIManager->Write(L"0", GUIManager::TextOrigin::CENTRE, Vector2(mScoreLabelText->mPosition.x, mScoreLabelText->mPosition.y), Vector2(150, 0), L"AlienEncounters.spritefont",
		0.0f, 0.75f, Vector4(1.0f, 0.0f, 0.0f, 1.0f), true);

	// Creates a button that allows the user to resume the game
	mResumeGameButton = mGUIManager->CreateButton(L"button.png", L"AlienEncounters.spritefont", L"RESUME", 0, 0.35f, 0.65f,
		GUIManager::ButtonOrigin::CENTRE, GUIManager::ButtonPosition::CENTRE_MIDDLE, Vector2(0, 0),
		Vector2(0, 10), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector4(1.0f, 1.0f, 0.0f, 1.0f), std::bind(&GameScene::OnClick_ResumeGameButton, this), false);

	mPausedText = mGUIManager->Write(L"PAUSED", GUIManager::TextOrigin::CENTRE, GUIManager::TextPosition::CENTRE_TOP, Vector2(0, 250),
		L"AlienEncounters.spritefont", 0.0f, 1.5f, Vector4(1.0f, 0.0f, 0.0f, 1.0f), false);

	// Creates a button that allows the user to exit back to the main menu
	mPausedExitButton = mGUIManager->CreateButton(L"button.png", L"AlienEncounters.spritefont", L"MAIN MENU", 0, 0.35f, 0.65f,
		GUIManager::ButtonOrigin::CENTRE, GUIManager::ButtonPosition::CENTRE_MIDDLE, Vector2(0, 100),
		Vector2(0, 10), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector4(1.0f, 1.0f, 0.0f, 1.0f), std::bind(&GameScene::OnClick_MainMenuButton, this), false);


	mGameState = GAME_STATE::PLAYING;
}

/// <summary>
/// Clear up scene resources
/// </summary>
void GameScene::OnUnload()
{
	// Clears GUI from previous scene
	resourceManager->mSprites.clear();
	resourceManager->mButtons.clear();
	mGUIManager->GetQuads()->clear();
	mGUIManager->GetTextVector()->clear();

	mEcsManager->DestroyEntities();
}

/// <summary>
/// On pause logic
/// </summary>
void GameScene::OnPause()
{
	mGameState = GAME_STATE::PAUSED;
	//exit(0);

	// allows the user to use the mouse again as normal
	mInputManager->CenterCursor(false);
	mInputManager->CursorVisible(true);

	// TODO: STOP EVERYTHING IN THE GAME
	//mSceneManager->Pause(true);

	// make all of the pause menu attributes (GUI) visible
	//mPausedOverlay->mIsVisible = true;
	mPausedText->mIsVisible = true;
	mPausedExitButton->SetVisibility(true);
	mResumeGameButton->SetVisibility(true);

}

/// <summary>
/// On unpause logic
/// </summary>
void GameScene::OnUnPause()
{
	mGameState = GAME_STATE::PLAYING;

	// TODO: START EVERYTHING AGAIN
	//mSceneManager->Pause(false);

	//exit(0);
	//mPausedOverlay->mIsVisible = false;
	mPausedText->mIsVisible = false;
	mPausedExitButton->SetVisibility(false);
	mResumeGameButton->SetVisibility(false);

	// allows the user to use the centered mouse
	mInputManager->CenterCursor(true);
	mInputManager->CursorVisible(false);
}
