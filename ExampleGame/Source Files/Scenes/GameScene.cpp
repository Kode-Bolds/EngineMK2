#include "GameScene.h"

using namespace KodeboldsMath;

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
		int ID = mEcsManager->CreateEntity();
		Geometry geo{ L"cube.obj" };
		mEcsManager->AddGeometryComp(geo, ID);
		Shader shader{ L"defaultShader.fx" };
		mEcsManager->AddShaderComp(shader, ID);
		Transform transC{};
		transC.scale = Vector4(1, 1, 1, 1);
		transC.translation = mEcsManager->TransformComp(mPlayer)->translation + Vector4(-25, 5, 0, 0);
		transC.transform *= TranslationMatrix(transC.translation);
		mEcsManager->AddTransformComp(transC, ID);
		Velocity vel{};
		vel.acceleration = Vector4(0, 0.0f, 20.0f, 1);
		vel.maxSpeed = 40;
		mEcsManager->AddVelocityComp(vel, ID);
		Colour colour{Vector4(0, 0.4f, 0.8f, 1)};
		mEcsManager->AddColourComp(colour, ID);


		ID = mEcsManager->CreateEntity();
		Geometry geo2{ L"cube.obj" };
		mEcsManager->AddGeometryComp(geo2, ID);
		Shader shader2{ L"defaultShader.fx" };
		mEcsManager->AddShaderComp(shader2, ID);
		Transform transC2{};
		transC2.scale = Vector4(1, 1, 1, 1);
		transC2.translation = mEcsManager->TransformComp(mPlayer)->translation + Vector4(25, 5, 0, 0);
		transC2.transform *= TranslationMatrix(transC2.translation);
		mEcsManager->AddTransformComp(transC2, ID);
		Velocity vel2{};
		vel2.acceleration = Vector4(0, 0.0f, 20.0f, 1);
		vel2.maxSpeed = 40;
		mEcsManager->AddVelocityComp(vel2, ID);
		Colour colour2{ Vector4(0, 0.4f, 0.8f, 1) };
		mEcsManager->AddColourComp(colour2, ID);
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
	Shader shader{ L"defaultShader.fx" };
	mEcsManager->AddShaderComp(shader, mPlayer);
	Transform transC{};
	transC.scale = Vector4(1, 1, 1, 1);
	mEcsManager->AddTransformComp(transC, mPlayer);
	Velocity vel{};
	vel.acceleration = Vector4(0, 0.0f, 0, 1);
	vel.maxSpeed = 50;
	mEcsManager->AddVelocityComp(vel, mPlayer);
	//Gravity grav{};
	//mEcsManager->AddGravityComp(grav, mPlayer);
	//SphereCollider sphere{ 1 };
	//mEcsManager->AddSphereColliderComp(sphere, mPlayer);
	Colour colour2{ Vector4(1, 0, 0, 1) };
	mEcsManager->AddColourComp(colour2, mPlayer);

	mPlayerSpeed = 2.0f;

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
