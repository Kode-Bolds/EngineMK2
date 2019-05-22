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
	else if(mInputManager->KeyUp(KEYS::KEY_LEFT_SHIFT))
	{
		mPlayerSpeed /= 2;
	}

	//
	if (mInputManager->KeyDown(KEYS::MOUSE_BUTTON_LEFT))
	{
		Vector4 leftLaser = mEcsManager->TransformComp(mPlayer)->translation + Vector4(-25, 5, 0, 0);
		SpawnLaser(leftLaser, Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 1), Vector4(1, 0, 0, 1), Vector4(0, 0, 20, 1), 40,
			leftLaser.XYZ() - Vector3(1, 1, 1), leftLaser.XYZ() + Vector3(1, 1, 1), CustomCollisionMask::LASER | CustomCollisionMask::PLAYER);

		Vector4 rightLaser = mEcsManager->TransformComp(mPlayer)->translation + Vector4(25, 5, 0, 0);
		SpawnLaser(rightLaser, Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 1), Vector4(1, 0, 0, 1), Vector4(0, 0, 20, 1), 40,
			rightLaser.XYZ() - Vector3(1, 1, 1), rightLaser.XYZ() + Vector3(1, 1, 1), CustomCollisionMask::LASER | CustomCollisionMask::PLAYER );
	}

	//If player collides with floor
	if (mEcsManager->CollisionComp(mCamera))
	{
		if (mEcsManager->CollisionComp(mCamera)->collidedEntityCollisionMask == CustomCollisionMask::FLOOR)
		{
			mEcsManager->VelocityComp(mCamera)->velocity.Y = -mEcsManager->VelocityComp(mCamera)->velocity.Y;
			mEcsManager->TransformComp(mCamera)->translation.Y += mEcsManager->VelocityComp(mCamera)->velocity.Y * mSceneManager->DeltaTime();
		}
	}
}

/// <summary>
/// Scene setup on load
/// </summary>
void GameScene::OnLoad()
{
	//Spawn camera
	mCamera = mEcsManager->CreateEntity();
	Camera cam{ 60, 1, 200, true };

	mEcsManager->AddCameraComp(cam, mCamera);
	Transform trans{};
	trans.translation = Vector4(0, 10, -100, 1);
	trans.scale = Vector4(1, 1, 1, 1);
	mEcsManager->AddTransformComp(trans, mCamera);
	//BoxCollider camBox{ trans.translation.XYZ() - Vector3(1, 2, 1), trans.translation.XYZ() + Vector3(1, 2, 1), CustomCollisionMask::PLAYER, CustomCollisionMask::PLAYER };
	//mEcsManager->AddBoxColliderComp(camBox, mCamera);
	//Gravity gravCam{};
	//mEcsManager->AddGravityComp(gravCam, mCamera);
	//Velocity velCam{};
	//velCam.maxSpeed = 10;
	//mEcsManager->AddVelocityComp(velCam, mCamera);

	mCameraSpeed = 10.0f;

	//Spawn player ship
	mPlayer = mEcsManager->CreateEntity();
	Geometry geo{ L"ship.obj" };
	mEcsManager->AddGeometryComp(geo, mPlayer);
	Shader shader{ L"defaultShader.fx" , BlendState::NOBLEND, CullState::BACK, DepthState::NONE };
	mEcsManager->AddShaderComp(shader, mPlayer);
	Texture texture{};
	texture.diffuse = L"stones.dds";
	texture.normal = L"stones_NM_height.dds";
	mEcsManager->AddTextureComp(texture, mPlayer);
	Transform transC{};
	transC.translation = Vector4(0, 0, -50, 1);
	transC.scale = Vector4(1, 1, 1, 1);
	mEcsManager->AddTransformComp(transC, mPlayer);
	Velocity vel{};
	vel.acceleration = Vector4(0, 0.0f, 0, 1);
	vel.maxSpeed = 50;
	mEcsManager->AddVelocityComp(vel, mPlayer);
	Colour colour2{ Vector4(1, 1, 1, 1) };
	mEcsManager->AddColourComp(colour2, mPlayer);

	mPlayerSpeed = 2.0f;

	//Spawn laser gun
	int gun = mEcsManager->CreateEntity();
	Geometry geo2{ L"laser_gun.obj" };
	mEcsManager->AddGeometryComp(geo2, gun);
	Shader shader2{ L"defaultShader.fx" , BlendState::NOBLEND, CullState::BACK, DepthState::NONE };
	mEcsManager->AddShaderComp(shader2, gun);
	Texture texture2{};
	texture2.diffuse = L"stones.dds";
	texture2.normal = L"stones_NM_height.dds";
	mEcsManager->AddTextureComp(texture2, gun);
	Transform transC2{};
	transC2.translation = Vector4(0, 2, -50, 1);
	transC2.scale = Vector4(2.0f, 2.0f, 2.0f, 1);
	mEcsManager->AddTransformComp(transC2, gun);

	//Spawn platform of cubes
	for(int x = 0; x < 10; x++)
	{
		for(int z = 0; z < 10; z++)
		{
			int entity = mEcsManager->CreateEntity();

			Geometry geom{ L"cube.obj" };
			mEcsManager->AddGeometryComp(geom, entity);
			Shader shaderm{ L"defaultShader.fx" , BlendState::NOBLEND, CullState::BACK, DepthState::NONE };
			mEcsManager->AddShaderComp(shaderm, entity);
			Texture texturem{};
			texturem.diffuse = L"stones.dds";
			texturem.normal = L"stones_NM_height.dds";
			mEcsManager->AddTextureComp(texturem, entity);
			Transform transCm{};
			transCm.scale = Vector4(1, 1, 1, 1);
			transCm.translation = Vector4(x * 2 - 5, -2, z * 2- 100, 1);
			mEcsManager->AddTransformComp(transCm, entity);
			BoxCollider floorBox{ transCm.translation.XYZ() - Vector3(1, 1, 1), transCm.translation.XYZ() + Vector3(1, 1, 1), CustomCollisionMask::FLOOR, CustomCollisionMask::FLOOR };
			mEcsManager->AddBoxColliderComp(floorBox, entity);
		}
	}

	//Skybox
	int entity = mEcsManager->CreateEntity();

	Geometry geom{ L"cube.obj" };
	mEcsManager->AddGeometryComp(geom, entity);
	Shader shaderm{ L"skyboxShader.fx" , BlendState::ALPHABLEND, CullState::FRONT, DepthState::LESSEQUAL };
	mEcsManager->AddShaderComp(shaderm, entity);
	Texture texturem{};
	texturem.diffuse = L"";
	texturem.normal = L"";
	mEcsManager->AddTextureComp(texturem, entity);

	Transform transCm{};
	transCm.scale = Vector4(1, 1, 1, 1);
	transCm.translation = Vector4(0,0, 0, 1);



	mEcsManager->AddTransformComp(transCm, entity);


	//Spawn some asteroids
	for (int i = -20; i < 20; i++)
	{
		for (int j = -5; j < 5; j++)
		{
			for (int k = 10; k > 2; k--)
			{
				SpawnAsteroid(Vector4(5 * i, 5 * j, 10 * k, 1), Vector4(5, 5, 5, 1), Vector4(0, 0, 0, 1), 5, CustomCollisionMask::ASTEROID, L"stones.dds", L"stones_NM_height.dds");
			}
		}
	}

	const int dLight = mEcsManager->CreateEntity();
	DirectionalLight dl{Vector4(0,-1,-1,1), Vector4(1,0,0,1)};
	mEcsManager->AddDirectionalLightComp(dl, dLight);

	const int dLight2 = mEcsManager->CreateEntity();
	DirectionalLight dl2{ Vector4(1,-1,1,1), Vector4(0,1,0,1) };
	mEcsManager->AddDirectionalLightComp(dl2, dLight2);

	const int pLight = mEcsManager->CreateEntity();
	PointLight pl{ Vector4(0,1,0,1), 2};
	mEcsManager->AddPointLightComp(pl, pLight);
	Transform t;
	t.translation = Vector4(0 * 2 - 5, -2, 0 * 2 - 100, 1);
	t.scale = Vector4(1,1,1,1);
	mEcsManager->AddTransformComp(t, pLight);

	const int pLight2 = mEcsManager->CreateEntity();
	PointLight pl2{ Vector4(0,0.5,0.3,1), 2};
	mEcsManager->AddPointLightComp(pl2, pLight2);
	Transform t2;
	t2.translation = Vector4(10 * 2 - 5, -2, 0 * 2 - 100, 1);
	t2.scale = Vector4(1, 1, 1, 1);
	mEcsManager->AddTransformComp(t2, pLight2);

	const int pLight3 = mEcsManager->CreateEntity();
	PointLight pl3{ Vector4(0.3,1,0,1), 2};
	mEcsManager->AddPointLightComp(pl3, pLight3);
	Transform t3;
	t3.translation = Vector4(0 * 2 - 5, -2, 10 * 2 - 100, 1);
	t3.scale = Vector4(1, 1, 1, 1);
	mEcsManager->AddTransformComp(t3, pLight3);

	const int pLight4 = mEcsManager->CreateEntity();
	PointLight pl4{ Vector4(0.3,0.5,0.2,1) , 2};
	mEcsManager->AddPointLightComp(pl4, pLight4);
	Transform t4;
	t4.translation = Vector4(10 * 2 - 5, -2, 10 * 2 - 100, 1);
	t4.scale = Vector4(1, 1, 1, 1);
	mEcsManager->AddTransformComp(t4, pLight4);

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
