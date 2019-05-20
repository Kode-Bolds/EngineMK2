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
		mEcsManager->VelocityComp(mPlayer)->acceleration.Z = mPlayerSpeed;
	}
	else if (mInputManager->KeyHeld(KEYS::KEY_S))
	{
		mEcsManager->VelocityComp(mPlayer)->acceleration.Z = -mPlayerSpeed;
	}
	else
	{
		mEcsManager->VelocityComp(mPlayer)->acceleration.Z = 0;
	}

	//
	if (mInputManager->KeyHeld(KEYS::KEY_A))
	{
		mEcsManager->VelocityComp(mPlayer)->acceleration.X = -mPlayerSpeed;
	}
	else if (mInputManager->KeyHeld(KEYS::KEY_D))
	{
		mEcsManager->VelocityComp(mPlayer)->acceleration.X = mPlayerSpeed;
	}
	else
	{
		mEcsManager->VelocityComp(mPlayer)->acceleration.X = 0;
	}

	//
	if (mInputManager->KeyHeld(KEYS::KEY_SPACE))
	{
		mEcsManager->VelocityComp(mPlayer)->acceleration.Y = mPlayerSpeed;
	}
	else if (mInputManager->KeyHeld(KEYS::KEY_LEFT_CTRL))
	{
		mEcsManager->VelocityComp(mPlayer)->acceleration.Y = -mPlayerSpeed;
	}
	else
	{
		mEcsManager->VelocityComp(mPlayer)->acceleration.Y = 0;
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

	if (mInputManager->KeyDown(KEYS::MOUSE_BUTTON_LEFT))
	{
		Vector4 leftLaser = mEcsManager->TransformComp(mPlayer)->translation + Vector4(-25, 5, 0, 0);
		SpawnLaser(leftLaser, Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 1), Vector4(1, 0, 0, 1), Vector4(0, 0, 20, 1), 40,
			leftLaser.XYZ() - Vector3(1, 1, 1), leftLaser.XYZ() + Vector3(1, 1, 1), CustomCollisionMask::LASER | CustomCollisionMask::PLAYER);

		Vector4 rightLaser = mEcsManager->TransformComp(mPlayer)->translation + Vector4(25, 5, 0, 0);
		SpawnLaser(rightLaser, Vector4(1, 1, 1, 1), Vector4(0, 0, 0, 1), Vector4(1, 0, 0, 1), Vector4(0, 0, 20, 1), 40,
			rightLaser.XYZ() - Vector3(1, 1, 1), rightLaser.XYZ() + Vector3(1, 1, 1), CustomCollisionMask::LASER | CustomCollisionMask::PLAYER);
	}
}

/// <summary>
/// Scene setup on load
/// </summary>
void GameScene::OnLoad()
{
	mPlayer = mEcsManager->CreateEntity();
	Geometry geo{ L"ship.obj" };
	mEcsManager->AddGeometryComp(geo, mPlayer);
	Shader shader{ L"defaultShader.fx" , BlendState::ALPHABLEND, CullState::WIREFRAME, DepthState::LESSEQUAL };
	mEcsManager->AddShaderComp(shader, mPlayer);
	Transform transC{};
	transC.scale = Vector4(1, 1, 1, 1);
	mEcsManager->AddTransformComp(transC, mPlayer);
	Velocity vel{};
	vel.acceleration = Vector4(0, 0.0f, 0, 1);
	vel.maxSpeed = 50;
	mEcsManager->AddVelocityComp(vel, mPlayer);
	Colour colour2{ Vector4(1, 0, 0, 1) };
	mEcsManager->AddColourComp(colour2, mPlayer);

	mPlayerSpeed = 2.0f;

	//AntTweak
	mAntTweakManager->AddBar("Testing");
	TwDefine(" Testing size='300 320' valueswidth=200 ");
	mAntTweakManager->AddVariable("Testing", "Velocity", TW_TYPE_DIR3F, &mEcsManager->VelocityComp(mPlayer)->velocity, "");
	mAntTweakManager->AddVariable("Testing", "Acceleration", TW_TYPE_DIR3F, &mEcsManager->VelocityComp(mPlayer)->acceleration, "");
	mAntTweakManager->AddVariable("Testing", "Max Speed", TW_TYPE_FLOAT, &mEcsManager->VelocityComp(mPlayer)->maxSpeed, "");
}

/// <summary>
/// Clear up scene resources
/// </summary>
void GameScene::OnUnload()
{
}
