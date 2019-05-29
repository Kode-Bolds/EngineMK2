#pragma once
#include "Scene.h"
#include <memory>
#include "NetworkManager.h"
#include "InputManager_DX.h"
#include "InputManager_GL.h"
#include "SceneManager.h"
#include "EntitySpawner.h"
#include "GUIManager.h"
#include "MenuScene.h"

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

	enum GAME_STATE {
		PLAYING,
		PAUSED,
		LOADING
	};
	GAME_STATE mGameState = GAME_STATE::LOADING;

	int mPlayer;
	int mPlayerGun;
	int mPlayerShip;
	int mPlayerShipCam;
	int mCamera;
	float mPlayerSpeed;
	float mPlayerJumpSpeed;
	float mShipSpeed;
	float mCameraSpeed;
	float mRotationSpeed;

	KodeboldsMath::Vector4 mPlayerShipStartPos;
	KodeboldsMath::Vector4 mPlayerStartPos;
	KodeboldsMath::Vector4 mFreeCamStartPos;

	bool mPlayerIsGrounded;

	void Movement();
	void Rotation();
	void Shooting();
	void RotateAroundPoint(const int pEntity, const KodeboldsMath::Vector4& pAxis, const KodeboldsMath::Vector4& pPoint, const float& pAngle);

	int mLives = 3;
	std::vector<Sprite*> mLivesVector;

	int mBullets = 10;
	std::vector<Sprite*> mBulletVector;

	// PAUSED ASSETS
	Quad* mPausedOverlay = nullptr;
	Text* mPausedText = nullptr;
	Button* mPausedExitButton = nullptr;
	Button* mResumeGameButton = nullptr;


	void OnClick_MainMenuButton();
	void OnClick_ResumeGameButton();


public:
	//Structors
	GameScene();
	~GameScene();

	void Update() override;
	void OnLoad() override;
	void OnUnload() override;
	void OnPause();
	void OnUnPause();
};
