#include "GameScene.h"

using namespace KodeboldsMath;
using namespace EntitySpawner;

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
	//
	if (mInputManager->KeyHeld(KEYS::KEY_W))
	{
		//mEcsManager->VelocityComp(mPlayer)->acceleration.Z = mPlayerSpeed;
		mEcsManager->TransformComp(mCamera)->translation += mEcsManager->TransformComp(mCamera)->forward * mCameraSpeed * mSceneManager->DeltaTime();
	}
	else if (mInputManager->KeyHeld(KEYS::KEY_S))
	{
		//mEcsManager->VelocityComp(mPlayer)->acceleration.Z = -mPlayerSpeed;
		mEcsManager->TransformComp(mCamera)->translation -= mEcsManager->TransformComp(mCamera)->forward * mCameraSpeed * mSceneManager->DeltaTime();
	}
	else
	{
		//mEcsManager->VelocityComp(mPlayer)->acceleration.Z = 0;
	}

	//
	if (mInputManager->KeyHeld(KEYS::KEY_A))
	{
		//mEcsManager->VelocityComp(mPlayer)->acceleration.X = -mPlayerSpeed;
		mEcsManager->TransformComp(mCamera)->translation -= mEcsManager->TransformComp(mCamera)->right * mCameraSpeed * mSceneManager->DeltaTime();
	}
	else if (mInputManager->KeyHeld(KEYS::KEY_D))
	{
		//mEcsManager->VelocityComp(mPlayer)->acceleration.X = mPlayerSpeed;
		mEcsManager->TransformComp(mCamera)->translation += mEcsManager->TransformComp(mCamera)->right * mCameraSpeed * mSceneManager->DeltaTime();
	}
	else
	{
		//mEcsManager->VelocityComp(mPlayer)->acceleration.X = 0;
	}

	//
	if (mInputManager->KeyHeld(KEYS::KEY_SPACE))
	{
		//mEcsManager->VelocityComp(mPlayer)->acceleration.Y = mPlayerSpeed;
		mEcsManager->TransformComp(mCamera)->translation += mEcsManager->TransformComp(mCamera)->up * mCameraSpeed * mSceneManager->DeltaTime();
	}
	else if (mInputManager->KeyHeld(KEYS::KEY_LEFT_CTRL))
	{
		//mEcsManager->VelocityComp(mPlayer)->acceleration.Y = -mPlayerSpeed;
		mEcsManager->TransformComp(mCamera)->translation -= mEcsManager->TransformComp(mCamera)->up * mCameraSpeed * mSceneManager->DeltaTime();
	}
	else
	{
		//mEcsManager->VelocityComp(mPlayer)->acceleration.Y = 0;
	}

	//
	if (mInputManager->KeyHeld(KEYS::KEY_Q))
	{
		mEcsManager->TransformComp(mCamera)->rotation -= Vector4(0, 1, 0, 0) * mSceneManager->DeltaTime();
	}
	if (mInputManager->KeyHeld(KEYS::KEY_E))
	{
		mEcsManager->TransformComp(mCamera)->rotation += Vector4(0, 1, 0, 0) * mSceneManager->DeltaTime();
	}

	//
	if (mInputManager->KeyDown(KEYS::KEY_LEFT_SHIFT))
	{
		mPlayerSpeed *= 2;
	}
<<<<<<< HEAD
	else if (mInputManager->KeyUp(KEYS::KEY_LEFT_SHIFT))
=======
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
<<<<<<< HEAD
>>>>>>> parent of 0f257ec... Merge branch 'master' into master
=======
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
>>>>>>> parent of 0f257ec... Merge branch 'master' into master
	{
		mPlayerSpeed /= 2;
	}

	//
	if (mInputManager->KeyDown(KEYS::MOUSE_BUTTON_LEFT))
	{
<<<<<<< HEAD
<<<<<<< HEAD
		Vector4 leftLaser = mEcsManager->TransformComp(mPlayer)->translation + Vector4(-25, 5, 0, 0);
		SpawnLaser(leftLaser, Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 1), Vector4(1, 0, 0, 1), Vector4(0, 0, 20, 1), 40,
			leftLaser.XYZ() - Vector3(1, 1, 1), leftLaser.XYZ() + Vector3(1, 1, 1), CustomCollisionMask::LASER | CustomCollisionMask::PLAYER, mLaserSound);

		Vector4 rightLaser = mEcsManager->TransformComp(mPlayer)->translation + Vector4(25, 5, 0, 0);
		SpawnLaser(rightLaser, Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 1), Vector4(1, 0, 0, 1), Vector4(0, 0, 20, 1), 40,
			rightLaser.XYZ() - Vector3(1, 1, 1), rightLaser.XYZ() + Vector3(1, 1, 1), CustomCollisionMask::LASER | CustomCollisionMask::PLAYER, mLaserSound);
=======
		mEcsManager->AddGravityComp(Gravity{}, mPlayer);
		mEcsManager->AddGravityComp(Gravity{}, mPlayerGun);
>>>>>>> parent of 0f257ec... Merge branch 'master' into master
=======
		mEcsManager->AddGravityComp(Gravity{}, mPlayer);
		mEcsManager->AddGravityComp(Gravity{}, mPlayerGun);
>>>>>>> parent of 0f257ec... Merge branch 'master' into master
	}
}

/// <summary>
/// Scene setup on load
/// </summary>
void GameScene::OnLoad()
{
<<<<<<< HEAD
<<<<<<< HEAD
	// Audio Files
	mLaserSound = resourceManager->LoadAudio(L"laser.wav");
	mEngineSound = resourceManager->LoadAudio(L"engine.wav");

	mCamera = mEcsManager->CreateEntity();
	Camera cam{ 60, 1, 200 };
	mEcsManager->AddCameraComp(cam, mCamera);
	Transform trans{};
	trans.translation = Vector4(0, 0, -100, 1);
	trans.scale = Vector4(1, 1, 1, 1);
	mEcsManager->AddTransformComp(trans, mCamera);
	mCameraSpeed = 10.0f;

	mPlayer = mEcsManager->CreateEntity();
	Geometry geo{ L"ship.obj" };
	mEcsManager->AddGeometryComp(geo, mPlayer);
	Shader shader{ L"depthShader.fx" , BlendState::ALPHABLEND, CullState::BACK, DepthState::LESSEQUAL };
	mEcsManager->AddShaderComp(shader, mPlayer);
	Texture texture{};
	texture.diffuse = L"stones.dds";
	texture.normal = L"stones_NM_height.dds";
	mEcsManager->AddTextureComp(texture, mPlayer);

	//// Audio Component
	//Audio audio{};
	//audio.mSound = mEngineSound;
	//audio.active = true;
	//audio.loop = false;
	//entitySpawnerEcsManager->AddAudioComp(audio, mPlayer);

	Transform transC{};
	transC.scale = Vector4(1, 1, 1, 1);
	mEcsManager->AddTransformComp(transC, mPlayer);
	Velocity vel{};
	vel.acceleration = Vector4(0, 0.0f, 0, 1);
	vel.maxSpeed = 50;
	mEcsManager->AddVelocityComp(vel, mPlayer);
	Colour colour2{ Vector4(1, 1, 1, 1) };
	mEcsManager->AddColourComp(colour2, mPlayer);

	mPlayerSpeed = 2.0f;


	for (int x = 0; x < 10; x++)
=======
=======
>>>>>>> parent of 0f257ec... Merge branch 'master' into master
	//Spawn player ship and attached camera
	mPlayerShipStartPos = Vector4(0, 0, -50, 1);
	mPlayerShip = SpawnShip(mPlayerShipStartPos, Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 0), 40, mPlayerShipStartPos.XYZ() - Vector3(30, 30, 15), mPlayerShipStartPos.XYZ() + Vector3(30, 30, 15),
		CustomCollisionMask::SHIP, CustomCollisionMask::SHIP | CustomCollisionMask::LASER | CustomCollisionMask::PLAYER, L"stones.dds", L"stones_NM_height.dds");
	mPlayerShipCam = SpawnCamera(mPlayerShipStartPos + Vector4(0, 30, -70, 1), Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 0), 60, 1, 400, 40);
	mEcsManager->CameraComp(mPlayerShipCam)->active = true;

	//Spawn player camera and attached laser gun model
	mPlayerStartPos = Vector4(0, 50, -100, 1);
	mPlayer = SpawnPlayer(mPlayerStartPos, Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 0), 60, 1, 400, 5, mPlayerStartPos.XYZ() - Vector3(1, 2, 1), mPlayerStartPos.XYZ() + Vector3(1, 2, 1),
		CustomCollisionMask::PLAYER, CustomCollisionMask::PLAYER | CustomCollisionMask::LASER | CustomCollisionMask::SHIP);
	mPlayerGun = SpawnLaserGun(mPlayerStartPos + Vector4(1, -1, 3.0f, 0), Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 1), L"stones.dds", L"stones_NM_height.dds", 5);

	//Spawn free cam
	mCamera = SpawnCamera(Vector4(5, 2, -100, 1), Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 0), 60, 1, 400, 20);

	//Set acceleration speeds
	mPlayerSpeed = 10.0f;
	mPlayerJumpSpeed = 20.0f;
	mShipSpeed = 20.0f;
	mCameraSpeed = 20.0f;

	//Spawn platform of cubes
	for(int x = 0; x < 10; x++)
<<<<<<< HEAD
>>>>>>> parent of 0f257ec... Merge branch 'master' into master
=======
>>>>>>> parent of 0f257ec... Merge branch 'master' into master
	{
		for(int z = 0; z < 10; z++)
		{
			int entity = mEcsManager->CreateEntity();

			Geometry geom{ L"cube.obj" };
			mEcsManager->AddGeometryComp(geom, entity);
			Shader shaderm{ L"defaultShader.fx" , BlendState::ALPHABLEND, CullState::BACK, DepthState::LESSEQUAL };
			mEcsManager->AddShaderComp(shaderm, entity);
			Texture texturem{};
			texturem.diffuse = L"stones.dds";
			texturem.normal = L"stones_NM_height.dds";
			mEcsManager->AddTextureComp(texturem, entity);

			Transform transCm{};
			transCm.scale = Vector4(1, 1, 1, 1);
<<<<<<< HEAD
<<<<<<< HEAD
			transCm.translation = Vector4(x * 2 - 5, -2, z * 2 - 100, 1);

			if (x == 0 && z == 0)
			{
				//transCm.translation = Vector4(0, 0, -96, 1);

			}
=======
=======
>>>>>>> parent of 0f257ec... Merge branch 'master' into master
			transCm.translation = Vector4(x * 2 - 5, -2, z * 2- 100, 1);
			mEcsManager->AddTransformComp(transCm, entity);
			BoxCollider floorBox{ transCm.translation.XYZ() - Vector3(1, 1, 1), transCm.translation.XYZ() + Vector3(1, 1, 1), CustomCollisionMask::FLOOR, CustomCollisionMask::FLOOR };
			mEcsManager->AddBoxColliderComp(floorBox, entity);
		}
	}

	//Skybox
	int entity = mEcsManager->CreateEntity();
<<<<<<< HEAD
>>>>>>> parent of 0f257ec... Merge branch 'master' into master

			mEcsManager->AddTransformComp(transCm, entity);
=======

	Geometry geom{ L"cube.obj" };
	mEcsManager->AddGeometryComp(geom, entity);
	Shader shaderm{ L"skyboxShader.fx" , BlendState::ALPHABLEND, CullState::FRONT, DepthState::LESSEQUAL };
	mEcsManager->AddShaderComp(shaderm, entity);
	Transform transCm{};
	transCm.scale = Vector4(1, 1, 1, 1);
	transCm.translation = Vector4(0,0, 0, 1);
	mEcsManager->AddTransformComp(transCm, entity);
>>>>>>> parent of 0f257ec... Merge branch 'master' into master


		}
	}
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
