#pragma once
#include "Scene.h"
#include <memory>
#include "NetworkManager.h"
#include "InputManager_DX.h"
#include "InputManager_GL.h"
#include "SceneManager.h"
#include "EntitySpawner.h"
#include "GUIManager.h"
#include "GameScene.h"

class MenuScene : public Scene
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


	int mMenuMusic;

public:
	//Structors
	MenuScene();
	~MenuScene();

	void Update() override;
	void OnLoad() override;
	void OnUnload() override;
	void OnClick_PlayButton();
	void OnClick_ExitButton();
};
