#include "GameScene.h"

using namespace KodeboldsMath;
using namespace EntitySpawner;

/// <summary>
///
/// </summary>
void GameScene::Movement()
{
	//Forward movement
	if (mInputManager->KeyDown(KEYS::KEY_W))
	{
		//If ship cam is active, move ship
		if (mEcsManager->CameraComp(mPlayerShipCam)->active)
		{
			mEcsManager->VelocityComp(mPlayerShip)->acceleration += mEcsManager->TransformComp(mPlayerShip)->forward.Normalise() * mShipSpeed;
			mEcsManager->VelocityComp(mPlayerShipCam)->acceleration += mEcsManager->TransformComp(mPlayerShipCam)->forward.Normalise() * mShipSpeed;
		}
		//If player cam is active, move player cam
		if (mEcsManager->CameraComp(mPlayer)->active)
		{
			mEcsManager->VelocityComp(mPlayer)->acceleration += mEcsManager->TransformComp(mPlayer)->forward.Normalise() * mPlayerSpeed;
			mEcsManager->VelocityComp(mPlayerGun)->acceleration += mEcsManager->TransformComp(mPlayerGun)->forward.Normalise() * mPlayerSpeed;
		}
		//If free cam is active, move free cam
		if (mEcsManager->CameraComp(mCamera)->active)
		{
			mEcsManager->VelocityComp(mCamera)->acceleration += mEcsManager->TransformComp(mCamera)->forward.Normalise() * mCameraSpeed;
		}
	}
	else if (mInputManager->KeyUp(KEYS::KEY_W))
	{
		//If ship cam is active, move ship
		if (mEcsManager->CameraComp(mPlayerShipCam)->active)
		{
			mEcsManager->VelocityComp(mPlayerShip)->acceleration -= mEcsManager->TransformComp(mPlayerShip)->forward.Normalise() * mShipSpeed;
			mEcsManager->VelocityComp(mPlayerShipCam)->acceleration -= mEcsManager->TransformComp(mPlayerShipCam)->forward.Normalise() * mShipSpeed;
		}
		//If player cam is active, move player cam
		if (mEcsManager->CameraComp(mPlayer)->active)
		{
			mEcsManager->VelocityComp(mPlayer)->acceleration -= mEcsManager->TransformComp(mPlayer)->forward.Normalise() * mPlayerSpeed;
			mEcsManager->VelocityComp(mPlayerGun)->acceleration -= mEcsManager->TransformComp(mPlayerGun)->forward.Normalise() * mPlayerSpeed;
		}
		//If free cam is active, move free cam
		if (mEcsManager->CameraComp(mCamera)->active)
		{
			mEcsManager->VelocityComp(mCamera)->acceleration -= mEcsManager->TransformComp(mCamera)->forward.Normalise() * mCameraSpeed;
		}
	}

	//Backwards movement
	if (mInputManager->KeyDown(KEYS::KEY_S))
	{
		//If ship cam is active, move ship
		if (mEcsManager->CameraComp(mPlayerShipCam)->active)
		{
			mEcsManager->VelocityComp(mPlayerShip)->acceleration += mEcsManager->TransformComp(mPlayerShip)->forward.Normalise() * -mShipSpeed;
			mEcsManager->VelocityComp(mPlayerShipCam)->acceleration += mEcsManager->TransformComp(mPlayerShipCam)->forward.Normalise() * -mShipSpeed;
		}
		//If player cam is active, move player cam
		if (mEcsManager->CameraComp(mPlayer)->active)
		{
			mEcsManager->VelocityComp(mPlayer)->acceleration += mEcsManager->TransformComp(mPlayer)->forward.Normalise() * -mPlayerSpeed;
			mEcsManager->VelocityComp(mPlayerGun)->acceleration += mEcsManager->TransformComp(mPlayerGun)->forward.Normalise() * -mPlayerSpeed;
		}
		//If free cam is active, move free cam
		if (mEcsManager->CameraComp(mCamera)->active)
		{
			mEcsManager->VelocityComp(mCamera)->acceleration += mEcsManager->TransformComp(mCamera)->forward.Normalise() * -mCameraSpeed;
		}
	}
	else if (mInputManager->KeyUp(KEYS::KEY_S))
	{
		//If ship cam is active, move ship
		if (mEcsManager->CameraComp(mPlayerShipCam)->active)
		{
			mEcsManager->VelocityComp(mPlayerShip)->acceleration -= mEcsManager->TransformComp(mPlayerShip)->forward.Normalise() * -mShipSpeed;
			mEcsManager->VelocityComp(mPlayerShipCam)->acceleration -= mEcsManager->TransformComp(mPlayerShipCam)->forward.Normalise() * -mShipSpeed;
		}
		//If player cam is active, move player cam
		if (mEcsManager->CameraComp(mPlayer)->active)
		{
			mEcsManager->VelocityComp(mPlayer)->acceleration -= mEcsManager->TransformComp(mPlayer)->forward.Normalise() * -mPlayerSpeed;
			mEcsManager->VelocityComp(mPlayerGun)->acceleration -= mEcsManager->TransformComp(mPlayerGun)->forward.Normalise() * -mPlayerSpeed;
		}
		//If free cam is active, move free cam
		if (mEcsManager->CameraComp(mCamera)->active)
		{
			mEcsManager->VelocityComp(mCamera)->acceleration -= mEcsManager->TransformComp(mCamera)->forward.Normalise() * -mCameraSpeed;
		}
	}

	//Left movement
	if (mInputManager->KeyDown(KEYS::KEY_A))
	{
		//If ship cam is active, move ship
		if (mEcsManager->CameraComp(mPlayerShipCam)->active)
		{
			mEcsManager->VelocityComp(mPlayerShip)->acceleration += mEcsManager->TransformComp(mPlayerShip)->right.Normalise() * -mShipSpeed;
			mEcsManager->VelocityComp(mPlayerShipCam)->acceleration += mEcsManager->TransformComp(mPlayerShipCam)->right.Normalise() * -mShipSpeed;
		}
		//If player cam is active, move player cam
		if (mEcsManager->CameraComp(mPlayer)->active)
		{
			mEcsManager->VelocityComp(mPlayer)->acceleration += mEcsManager->TransformComp(mPlayer)->right.Normalise() * -mPlayerSpeed;
			mEcsManager->VelocityComp(mPlayerGun)->acceleration += mEcsManager->TransformComp(mPlayerGun)->right.Normalise() * -mPlayerSpeed;
		}
		//If free cam is active, move free cam
		if (mEcsManager->CameraComp(mCamera)->active)
		{
			mEcsManager->VelocityComp(mCamera)->acceleration += mEcsManager->TransformComp(mCamera)->right.Normalise() * -mCameraSpeed;
		}
	}
	else if (mInputManager->KeyUp(KEYS::KEY_A))
	{
		//If ship cam is active, move ship
		if (mEcsManager->CameraComp(mPlayerShipCam)->active)
		{
			mEcsManager->VelocityComp(mPlayerShip)->acceleration -= mEcsManager->TransformComp(mPlayerShip)->right.Normalise() * -mShipSpeed;
			mEcsManager->VelocityComp(mPlayerShipCam)->acceleration -= mEcsManager->TransformComp(mPlayerShipCam)->right.Normalise() * -mShipSpeed;
		}
		//If player cam is active, move player cam
		if (mEcsManager->CameraComp(mPlayer)->active)
		{
			mEcsManager->VelocityComp(mPlayer)->acceleration -= mEcsManager->TransformComp(mPlayer)->right.Normalise() * -mPlayerSpeed;
			mEcsManager->VelocityComp(mPlayerGun)->acceleration -= mEcsManager->TransformComp(mPlayerGun)->right.Normalise() * -mPlayerSpeed;
		}
		//If free cam is active, move free cam
		if (mEcsManager->CameraComp(mCamera)->active)
		{
			mEcsManager->VelocityComp(mCamera)->acceleration -= mEcsManager->TransformComp(mCamera)->right.Normalise() * -mCameraSpeed;
		}
	}

	//Right movement
	if (mInputManager->KeyDown(KEYS::KEY_D))
	{
		//If ship cam is active, move ship
		if (mEcsManager->CameraComp(mPlayerShipCam)->active)
		{
			mEcsManager->VelocityComp(mPlayerShip)->acceleration += mEcsManager->TransformComp(mPlayerShip)->right.Normalise() * mShipSpeed;
			mEcsManager->VelocityComp(mPlayerShipCam)->acceleration += mEcsManager->TransformComp(mPlayerShipCam)->right.Normalise() * mShipSpeed;
		}
		//If player cam is active, move player cam
		if (mEcsManager->CameraComp(mPlayer)->active)
		{
			mEcsManager->VelocityComp(mPlayer)->acceleration += mEcsManager->TransformComp(mPlayer)->right.Normalise() * mPlayerSpeed;
			mEcsManager->VelocityComp(mPlayerGun)->acceleration += mEcsManager->TransformComp(mPlayerGun)->right.Normalise() * mPlayerSpeed;
		}
		//If free cam is active, move free cam
		if (mEcsManager->CameraComp(mCamera)->active)
		{
			mEcsManager->VelocityComp(mCamera)->acceleration += mEcsManager->TransformComp(mCamera)->right.Normalise() * mCameraSpeed;
		}
	}
	else if (mInputManager->KeyUp(KEYS::KEY_D))
	{
		//If ship cam is active, move ship
		if (mEcsManager->CameraComp(mPlayerShipCam)->active)
		{
			mEcsManager->VelocityComp(mPlayerShip)->acceleration -= mEcsManager->TransformComp(mPlayerShip)->right.Normalise() * mShipSpeed;
			mEcsManager->VelocityComp(mPlayerShipCam)->acceleration -= mEcsManager->TransformComp(mPlayerShipCam)->right.Normalise() * mShipSpeed;
		}
		//If player cam is active, move player cam
		if (mEcsManager->CameraComp(mPlayer)->active)
		{
			mEcsManager->VelocityComp(mPlayer)->acceleration -= mEcsManager->TransformComp(mPlayer)->right.Normalise() * mPlayerSpeed;
			mEcsManager->VelocityComp(mPlayerGun)->acceleration -= mEcsManager->TransformComp(mPlayerGun)->right.Normalise() * mPlayerSpeed;
		}
		//If free cam is active, move free cam
		if (mEcsManager->CameraComp(mCamera)->active)
		{
			mEcsManager->VelocityComp(mCamera)->acceleration -= mEcsManager->TransformComp(mCamera)->right.Normalise() * mCameraSpeed;
		}
	}

	//Up movement
	if (mInputManager->KeyDown(KEYS::KEY_SPACE))
	{
		//If ship cam is active, move ship
		if (mEcsManager->CameraComp(mPlayerShipCam)->active)
		{
			mEcsManager->VelocityComp(mPlayerShip)->acceleration += mEcsManager->TransformComp(mPlayerShip)->up.Normalise() * mShipSpeed;
			mEcsManager->VelocityComp(mPlayerShipCam)->acceleration += mEcsManager->TransformComp(mPlayerShipCam)->up.Normalise() * mShipSpeed;
		}
		//If player cam is active, move player cam
		if (mEcsManager->CameraComp(mPlayer)->active && mPlayerIsGrounded)
		{
			mEcsManager->VelocityComp(mPlayer)->velocity += mEcsManager->TransformComp(mPlayer)->up.Normalise() * mPlayerJumpSpeed;
			mEcsManager->VelocityComp(mPlayerGun)->velocity += mEcsManager->TransformComp(mPlayerGun)->up.Normalise() * mPlayerJumpSpeed;
		}
		//If free cam is active, move free cam
		if (mEcsManager->CameraComp(mCamera)->active)
		{
			mEcsManager->VelocityComp(mCamera)->acceleration += mEcsManager->TransformComp(mCamera)->up.Normalise() * mCameraSpeed;
		}
	}
	else if (mInputManager->KeyUp(KEYS::KEY_SPACE))
	{
		//If ship cam is active, move ship
		if (mEcsManager->CameraComp(mPlayerShipCam)->active)
		{
			mEcsManager->VelocityComp(mPlayerShip)->acceleration -= mEcsManager->TransformComp(mPlayerShip)->up.Normalise() * mShipSpeed;
			mEcsManager->VelocityComp(mPlayerShipCam)->acceleration -= mEcsManager->TransformComp(mPlayerShipCam)->up.Normalise() * mShipSpeed;
		}
		//If free cam is active, move free cam
		if (mEcsManager->CameraComp(mCamera)->active)
		{
			mEcsManager->VelocityComp(mCamera)->acceleration -= mEcsManager->TransformComp(mCamera)->up.Normalise() * mCameraSpeed;
		}
	}

	//Down movement
	if (mInputManager->KeyDown(KEYS::KEY_LEFT_CTRL))
	{
		//If ship cam is active, move ship
		if (mEcsManager->CameraComp(mPlayerShipCam)->active)
		{
			mEcsManager->VelocityComp(mPlayerShip)->acceleration += mEcsManager->TransformComp(mPlayerShip)->up.Normalise() * -mShipSpeed;
			mEcsManager->VelocityComp(mPlayerShipCam)->acceleration += mEcsManager->TransformComp(mPlayerShipCam)->up.Normalise() * -mShipSpeed;

		}
		//If free cam is active, move free cam
		if (mEcsManager->CameraComp(mCamera)->active)
		{
			mEcsManager->VelocityComp(mCamera)->acceleration += mEcsManager->TransformComp(mCamera)->up.Normalise() * -mCameraSpeed;
		}
	}
	else if (mInputManager->KeyUp(KEYS::KEY_LEFT_CTRL))
	{
		//If ship cam is active, move ship
		if (mEcsManager->CameraComp(mPlayerShipCam)->active)
		{
			mEcsManager->VelocityComp(mPlayerShip)->acceleration -= mEcsManager->TransformComp(mPlayerShip)->up.Normalise() * -mShipSpeed;
			mEcsManager->VelocityComp(mPlayerShipCam)->acceleration -= mEcsManager->TransformComp(mPlayerShipCam)->up.Normalise() * -mShipSpeed;
		}
		//If free cam is active, move free cam
		if (mEcsManager->CameraComp(mCamera)->active)
		{
			mEcsManager->VelocityComp(mCamera)->acceleration -= mEcsManager->TransformComp(mCamera)->up.Normalise() * -mCameraSpeed;
		}
	}

	//Freeze currently active camera, removing all velocity
	if (mInputManager->KeyDown(KEYS::KEY_LEFT_SHIFT))
	{
		//If ship cam is active, freeze ship
		if (mEcsManager->CameraComp(mPlayerShipCam)->active)
		{
			mEcsManager->VelocityComp(mPlayerShip)->velocity = Vector4(0, 0, 0, 1);
			mEcsManager->VelocityComp(mPlayerShipCam)->velocity = Vector4(0, 0, 0, 1);
		}
		//If player cam is active, freeze player cam
		if (mEcsManager->CameraComp(mPlayer)->active)
		{
			mEcsManager->VelocityComp(mPlayer)->velocity = Vector4(0, 0, 0, 1);
			mEcsManager->VelocityComp(mPlayerGun)->velocity = Vector4(0, 0, 0, 1);
		}
		//If free cam is active, freeze free cam
		if (mEcsManager->CameraComp(mCamera)->active)
		{
			mEcsManager->VelocityComp(mCamera)->velocity = Vector4(0, 0, 0, 1);
		}
	}
}

/// <summary>
///
/// </summary>
void GameScene::Rotation()
{
	//Rotate left
	if (mInputManager->KeyHeld(KEYS::KEY_Q))
	{
		//If ship cam is active, rotate ship
		if (mEcsManager->CameraComp(mPlayerShipCam)->active)
		{
			mEcsManager->TransformComp(mPlayerShip)->transform *= RotationMatrixAxis(1 * mSceneManager->DeltaTime(), mEcsManager->TransformComp(mPlayerShip)->up.Normalise());
			auto translateToOrigin = TranslationMatrix(
				Vector4(-mEcsManager->TransformComp(mPlayerShip)->translation.X, -mEcsManager->TransformComp(mPlayerShip)->translation.Y, -mEcsManager->TransformComp(mPlayerShip)->translation.Z, 1));
			auto rotation = RotationMatrixAxis(-1 * mSceneManager->DeltaTime(), mEcsManager->TransformComp(mPlayerShip)->up.Normalise());
			auto translateBack = TranslationMatrix(mEcsManager->TransformComp(mPlayerShip)->translation);
			mEcsManager->TransformComp(mPlayerShipCam)->transform *= translateToOrigin * rotation * translateBack;
		}
		//If player cam is active, rotate player
		if (mEcsManager->CameraComp(mPlayer)->active)
		{
			mEcsManager->TransformComp(mPlayer)->transform *= RotationMatrixAxis(1 * mSceneManager->DeltaTime(), mEcsManager->TransformComp(mPlayer)->up);
			mEcsManager->TransformComp(mPlayerGun)->transform *= RotationMatrixAxis(-1 * mSceneManager->DeltaTime(), mEcsManager->TransformComp(mPlayer)->up);
		}
		//If free cam is active, rotate free cam
		if (mEcsManager->CameraComp(mCamera)->active)
		{
			mEcsManager->TransformComp(mCamera)->transform *= RotationMatrixAxis(-1 * mSceneManager->DeltaTime(), mEcsManager->TransformComp(mCamera)->up);
			//mEcsManager->TransformComp(mCamera)->transform *= RotationMatrixAxis(-1 * mSceneManager->DeltaTime(), Vector4(0,1,0,1));
			//mEcsManager->TransformComp(mCamera)->transform *= RotationMatrixY(-1 * mSceneManager->DeltaTime());
		}
	}
	//Rotate right
	if (mInputManager->KeyHeld(KEYS::KEY_E))
	{
		//If ship cam is active, rotate ship
		if (mEcsManager->CameraComp(mPlayerShipCam)->active)
		{
			mEcsManager->TransformComp(mPlayerShip)->transform *= RotationMatrixAxis(-1 * mSceneManager->DeltaTime(), mEcsManager->TransformComp(mPlayerShip)->up);
			mEcsManager->TransformComp(mPlayerShipCam)->transform *= RotationMatrixAxis(1 * mSceneManager->DeltaTime(), mEcsManager->TransformComp(mPlayerShip)->up);
		}
		//If player cam is active, rotate player
		if (mEcsManager->CameraComp(mPlayer)->active)
		{
			mEcsManager->TransformComp(mPlayer)->transform *= RotationMatrixAxis(-1 * mSceneManager->DeltaTime(), mEcsManager->TransformComp(mPlayer)->up);
			mEcsManager->TransformComp(mPlayerGun)->transform *= RotationMatrixAxis(1 * mSceneManager->DeltaTime(), mEcsManager->TransformComp(mPlayer)->up);
		}
		//If free cam is active, rotate free cam
		if (mEcsManager->CameraComp(mCamera)->active)
		{
			mEcsManager->TransformComp(mCamera)->transform *= RotationMatrixAxis(1 * mSceneManager->DeltaTime(), mEcsManager->TransformComp(mCamera)->up);
		}
	}
}

/// <summary>
///
/// </summary>
void GameScene::Shooting()
{
	//Fire on left click
	if (mInputManager->KeyDown(KEYS::MOUSE_BUTTON_LEFT))
	{
		//If ship cam is active, fire ship lasers
		if (mEcsManager->CameraComp(mPlayerShipCam)->active)
		{
			
			Vector4 leftLaser = mEcsManager->TransformComp(mPlayerShip)->translation + ((mEcsManager->TransformComp(mPlayerShip)->right * -23) + (mEcsManager->TransformComp(mPlayerShip)->up * 5));
			SpawnLaser(leftLaser, Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 1), Vector4(1, 0, 0, 1), mEcsManager->TransformComp(mPlayerShip)->forward * 40, 40,
				leftLaser.XYZ() - Vector3(1, 1, 1), leftLaser.XYZ() + Vector3(1, 1, 1), CustomCollisionMask::LASER | CustomCollisionMask::PLAYER, 100);

			Vector4 rightLaser = mEcsManager->TransformComp(mPlayerShip)->translation + ((mEcsManager->TransformComp(mPlayerShip)->right * 23) + (mEcsManager->TransformComp(mPlayerShip)->up * 5));
			SpawnLaser(rightLaser, Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 1), Vector4(1, 0, 0, 1), mEcsManager->TransformComp(mPlayerShip)->forward * 40, 40,
				rightLaser.XYZ() - Vector3(1, 1, 1), rightLaser.XYZ() + Vector3(1, 1, 1), CustomCollisionMask::LASER | CustomCollisionMask::PLAYER, 100);
		}

		//If player cam is active, fire gun
		if (mEcsManager->CameraComp(mPlayer)->active)
		{
			Vector4 gunBarrel = mEcsManager->TransformComp(mPlayerGun)->translation + (mEcsManager->TransformComp(mPlayerGun)->forward * -2);
			SpawnLaser(gunBarrel, Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 1), Vector4(1, 0, 0, 1), mEcsManager->TransformComp(mPlayerGun)->forward * -30, 40,
				gunBarrel.XYZ() - Vector3(1, 1, 1), gunBarrel.XYZ() + Vector3(1, 1, 1), CustomCollisionMask::LASER | CustomCollisionMask::PLAYER, 50);
		}
	}
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
	Movement();
	Rotation();
	Shooting();

	//Switch between cameras
	//Ship
	if (mInputManager->KeyDown(KEYS::KEY_F1))
	{
		mEcsManager->CameraComp(mPlayerShipCam)->active = true;
		mEcsManager->CameraComp(mPlayer)->active = false;
		mEcsManager->CameraComp(mCamera)->active = false;
	}
	//Player
	if (mInputManager->KeyDown(KEYS::KEY_F2))
	{
		mEcsManager->CameraComp(mPlayerShipCam)->active = false;
		mEcsManager->CameraComp(mPlayer)->active = true;
		mEcsManager->CameraComp(mCamera)->active = false;
	}
	//Free cam
	if (mInputManager->KeyDown(KEYS::KEY_F3))
	{
		mEcsManager->CameraComp(mPlayerShipCam)->active = false;
		mEcsManager->CameraComp(mPlayer)->active = false;
		mEcsManager->CameraComp(mCamera)->active = true;
	}

	//If the player doesn't have a gravity component
	if (!mEcsManager->GravityComp(mPlayer))
	{
		//Check if the player is colliding with something, else add gravity
		if (mEcsManager->CollisionComp(mPlayer))
		{
			//If it's not the floor, player is not grounded, add gravity
			if (!mEcsManager->CollisionComp(mPlayer)->collidedEntityCollisionMask == CustomCollisionMask::FLOOR)
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
}

/// <summary>
/// Scene setup on load
/// </summary>
void GameScene::OnLoad()
{
	//Audio Files
	mLaserSound = resourceManager->LoadAudio(L"laser.wav");
	mEngineSound = resourceManager->LoadAudio(L"engine.wav");

	//// Audio Component
	//Audio audio{};
	//audio.mSound = mEngineSound;
	//audio.active = true;
	//audio.loop = false;
	//entitySpawnerEcsManager->AddAudioComp(audio, mPlayer);

	mCamera = SpawnCamera(Vector4(5, 2, -100, 1), Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 0), 60, 1, 10000, 50);


	//Spawn player ship and attached camera
	mPlayerShipStartPos = Vector4(0, 0, -50, 1);
	mPlayerShip = SpawnShip(mPlayerShipStartPos, Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 1), 40, 60, CustomCollisionMask::SHIP, 
		CustomCollisionMask::SHIP | CustomCollisionMask::LASER | CustomCollisionMask::PLAYER | CustomCollisionMask::FLOOR, L"stones.dds", L"stones_NM_height.dds");
	mPlayerShipCam = SpawnCamera(mPlayerShipStartPos + Vector4(0, 40, -70, 1), Vector4(1, 1, 1, 1), Vector4(0.2f, 0, 0, 0), 60, 1, 400, 40);
	mEcsManager->CameraComp(mPlayerShipCam)->active = true;

	//Spawn player camera and attached laser gun model
	mPlayerStartPos = Vector4(0, 50, -100, 1);
	mPlayer = SpawnPlayer(mPlayerStartPos, Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 0), 60, 1, 400, 5, mPlayerStartPos.XYZ() - Vector3(1, 2, 1), mPlayerStartPos.XYZ() + Vector3(1, 2, 1),
		CustomCollisionMask::PLAYER, CustomCollisionMask::PLAYER | CustomCollisionMask::LASER | CustomCollisionMask::SHIP);
	mPlayerGun = SpawnLaserGun(mPlayerStartPos + Vector4(1, -1, 2.0f, 0), Vector4(1, 1, 1, 1), Vector4(0, 3.14f, 0, 1), L"laser_gun_diffuse.dds", L"laser_gun_normal.dds", 5);


	//Spawn free cam

	//Set acceleration speeds
	mPlayerSpeed = 10.0f;
	mPlayerJumpSpeed = 20.0f;
	mShipSpeed = 20.0f;
	mCameraSpeed = 20.0f;

	//Spawn platform of cubes
	//for (int x = 0; x < 10; x++)
	//{
	//	for (int z = 0; z < 10; z++)
	//	{
	//		int entity = mEcsManager->CreateEntity();

	//		Geometry geom{ L"cube.obj" };
	//		mEcsManager->AddGeometryComp(geom, entity);
	//		Shader shaderm{ L"defaultShader.fx" , BlendState::NOBLEND, CullState::BACK, DepthState::NONE };
	//		mEcsManager->AddShaderComp(shaderm, entity);
	//		Texture texturem{};
	//		texturem.diffuse = L"stones.dds";
	//		texturem.normal = L"stones_NM_height.dds";
	//		mEcsManager->AddTextureComp(texturem, entity);
	//		Transform transCm{};
	//		transCm.scale = Vector4(1, 1, 1, 1);
	//		transCm.translation = Vector4(x * 2 - 5, -2, z * 2 - 100, 1);

	//		mEcsManager->AddTransformComp(transCm, entity);
	//		BoxCollider floorBox{ transCm.translation.XYZ() - Vector3(1, 1, 1), transCm.translation.XYZ() + Vector3(1, 1, 1), CustomCollisionMask::FLOOR, CustomCollisionMask::FLOOR };
	//		mEcsManager->AddBoxColliderComp(floorBox, entity);
	//	}
	//}
	{
		int particleEntity = mEcsManager->CreateEntity();
		Geometry geom{ L"quad100.obj" };
		mEcsManager->AddGeometryComp(geom, particleEntity);
		Shader shaderm{ L"thrusterShader.fx" , BlendState::ALPHABLEND, CullState::FRONT, DepthState::LESSEQUAL };
		mEcsManager->AddShaderComp(shaderm, particleEntity);
		Texture texturem{};
		texturem.diffuse = L"";
		texturem.normal = L"";
		mEcsManager->AddTextureComp(texturem, particleEntity);

		Transform transCm{};
		transCm.scale = Vector4(10, 10, 10, 10);
		transCm.translation = Vector4(0, 0, 0, 1);

		mEcsManager->AddTransformComp(transCm, particleEntity);
	}

	{
		//Sun
		int entity = mEcsManager->CreateEntity();

		Geometry geom{ L"sphere.obj" };
		mEcsManager->AddGeometryComp(geom, entity);
		Shader shaderm{ L"sunShader.fx" , BlendState::ALPHABLEND, CullState::BACK, DepthState::LESSEQUAL };

		mEcsManager->AddShaderComp(shaderm, entity);
		Transform transCm{};
		transCm.translation = Vector4(0, 0, 1250, 1);

		transCm.scale = Vector4(500, 500, 500, 1);
		mEcsManager->AddTransformComp(transCm, entity);
	}

	{
		//Skybox
		int entity = mEcsManager->CreateEntity();

		Geometry geom{ L"cube.obj" };
		mEcsManager->AddGeometryComp(geom, entity);
		Shader shaderm{ L"skyboxShader.fx" , BlendState::ALPHABLEND, CullState::FRONT, DepthState::LESSEQUAL };
		mEcsManager->AddShaderComp(shaderm, entity);
		Transform transCm{};
		transCm.scale = Vector4(1, 1, 1, 1);
		transCm.translation = Vector4(0, 0, 0, 1);
		mEcsManager->AddTransformComp(transCm, entity);
	}

	//Spawn some asteroids
	for (int i = -20; i < 20; i++)
	{
		for (int j = -5; j < 5; j++)
		{
			for (int k = 10; k > 2; k--)
			{
				SpawnAsteroid(Vector4(20 * i, 20 * j, 40 * k, 1), Vector4(5, 5, 5, 1), Vector4(0, 0, 0, 1), 5, 0, L"stones.dds", L"stones_NM_height.dds");
			}
		}
	}

	const int dLight = mEcsManager->CreateEntity();
	DirectionalLight dl{Vector4(0,-1,-1,1), Vector4(0.5f,0.5f,0.5f,1)};
	mEcsManager->AddDirectionalLightComp(dl, dLight);

	//const int dLight2 = mEcsManager->CreateEntity();
	//DirectionalLight dl2{ Vector4(1,-1,1,1), Vector4(0,0.1f,0,1) };
	//mEcsManager->AddDirectionalLightComp(dl2, dLight2);

	const int pLight = mEcsManager->CreateEntity();
	PointLight pl{ Vector4(1.0f,1.0f,1.0f,1), 50};
	mEcsManager->AddPointLightComp(pl, pLight);
	Transform t;
	t.translation = Vector4(5, 20, -100, 1);
	t.scale = Vector4(1, 1, 1, 1);
	mEcsManager->AddTransformComp(t, pLight);

	//const int pLight2 = mEcsManager->CreateEntity();
	//PointLight pl2{ Vector4(0,0.2f,0.3f,1), 5};
	//mEcsManager->AddPointLightComp(pl2, pLight2);
	//Transform t2;
	//t2.translation = Vector4(5 * 2 - 5, 0, 2 * 2 - 100, 1);
	//t2.scale = Vector4(1, 1, 1, 1);
	//mEcsManager->AddTransformComp(t2, pLight2);

	//const int pLight3 = mEcsManager->CreateEntity();
	//PointLight pl3{ Vector4(0.3f,0.1f,0,1), 5};
	//mEcsManager->AddPointLightComp(pl3, pLight3);
	//Transform t3;
	//t3.translation = Vector4(2 * 2 - 5, 0, 5 * 2 - 100, 1);
	//t3.scale = Vector4(1, 1, 1, 1);
	//mEcsManager->AddTransformComp(t3, pLight3);

	//const int pLight4 = mEcsManager->CreateEntity();
	//PointLight pl4{ Vector4(0.3f,0.5f,0.2f,1) , 5};
	//mEcsManager->AddPointLightComp(pl4, pLight4);
	//Transform t4;
	//t4.translation = Vector4(5 * 2 - 5, 0, 5 * 2 - 100, 1);
	//t4.scale = Vector4(1, 1, 1, 1);
	//mEcsManager->AddTransformComp(t4, pLight4);

	//AntTweak
	mGUIManager->AddBar("Testing");
	TwDefine(" Testing size='300 320' valueswidth=200 ");
	mGUIManager->AddVariable("Testing", "Velocity", TW_TYPE_DIR3F, &mEcsManager->VelocityComp(mPlayer)->velocity, "");
	mGUIManager->AddVariable("Testing", "Acceleration", TW_TYPE_DIR3F, &mEcsManager->VelocityComp(mPlayer)->acceleration, "");
	mGUIManager->AddVariable("Testing", "Max Speed", TW_TYPE_FLOAT, &mEcsManager->VelocityComp(mPlayer)->maxSpeed, "");

}

/// <summary>
/// Clear up scene resources
/// </summary>
void GameScene::OnUnload()
{
}
