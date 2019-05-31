#include "LoadingScene.h"

using namespace KodeboldsMath;

/// <summary>
/// Default constructor
/// </summary>
LoadingScene::LoadingScene()
{
}

/// <summary>
/// Default destructor
/// </summary>
LoadingScene::~LoadingScene()
{
}

/// <summary>
/// Update loop for the scene
/// </summary>
void LoadingScene::Update()
{
}

/// <summary>
/// Scene setup on load
/// </summary>
void LoadingScene::OnLoad()
{
	// creates a panel that covers the screen when game is paused
	mOverlay = mGUIManager->CreateQuadOverlay(Vector4(0.1f, 0.1f, 0.1f, 1.0f), true);

	mLoadingText = mGUIManager->Write(L"LOADING", GUIManager::TextOrigin::CENTRE, GUIManager::TextPosition::CENTRE_MIDDLE, Vector2(0, 0), L"AlienEncounters.spritefont", 0.0f, 1.5f, Vector4(1.0f, 0.0f, 0.0f, 1.0f), true);

	Sleep(100);
	mSceneManager->LoadScene<GameScene>();
}

/// <summary>
/// Clear up scene resources
/// </summary>
void LoadingScene::OnUnload() {

}