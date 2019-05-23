#pragma once
#include "Scene.h"
#include <memory>
#include "NetworkManager.h"
#include "InputManager_DX.h"
#include "InputManager_GL.h"
#include "SceneManager.h"
#include "EntitySpawner.h"
#include "GUIManager.h"

class GameScene : public Scene
{
private:
	//Managers
	std::shared_ptr<ECSManager> mEcsManager = ECSManager::Instance();
	std::shared_ptr<NetworkManager> mNetworkManager = NetworkManager::Instance();
#ifdef  DIRECTX
	std::shared_ptr<InputManager_DX> mInputManager = InputManager_DX::Instance();
#elif OPENGL
	std::shared_ptr<InputManager_GL> mInputManager = InputManager_GL::Instance();
#endif
	std::shared_ptr<SceneManager> mSceneManager = SceneManager::Instance();
	std::shared_ptr<GUIManager> mGUIManager = GUIManager::Instance();
	std::shared_ptr<ResourceManager> resourceManager = ResourceManager::Instance();

	int mPlayer;
	int mPlayerGun;
	int mPlayerShip;
	int mPlayerShipCam;
	int mCamera;
	float mPlayerSpeed;
	float mPlayerJumpSpeed;
	float mShipSpeed;
	float mCameraSpeed;

	KodeboldsMath::Vector4 mPlayerShipStartPos;
	KodeboldsMath::Vector4 mPlayerStartPos;
	KodeboldsMath::Vector4 mFreeCamStartPos;

	void Movement();
	void Rotation();
	void Shooting();

	Sound* mLaserSound = nullptr;
	Sound* mEngineSound = nullptr;

public:
	//Structors
	GameScene();
	~GameScene();

	void Update() override;
	void OnLoad() override;
	void OnUnload() override;
};
