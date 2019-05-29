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

class LoadingScene : public Scene
{
private:
	//Managers
	std::shared_ptr<ECSManager> mEcsManager = ECSManager::Instance();
	std::shared_ptr<SceneManager> mSceneManager = SceneManager::Instance();
	std::shared_ptr<GUIManager> mGUIManager = GUIManager::Instance();
	std::shared_ptr<ResourceManager> resourceManager = ResourceManager::Instance();

	Quad* mOverlay = nullptr;
	Text* mLoadingText = nullptr;


public:
	//Structors
	LoadingScene();
	~LoadingScene();

	void Update() override;
	void OnLoad() override;
	void OnUnload() override;
};
