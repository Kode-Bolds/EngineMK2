#include "MenuScene.h"

using namespace KodeboldsMath;

/// <summary>
/// Default constructor
/// </summary>
MenuScene::MenuScene()
{
}

/// <summary>
/// Default destructor
/// </summary>
MenuScene::~MenuScene()
{
}

/// <summary>
/// Update loop for the scene
/// </summary>
void MenuScene::Update()
{

	//Switch between cameras
	//Ship
#ifdef  DIRECTX
	if (mInputManager->KeyDown(KEYS::KEY_ENTER))
	{
		mSceneManager->LoadScene<GameScene>();
	}
#elif OPENGL
#endif
}

/// <summary>
/// Scene setup on load
/// </summary>
void MenuScene::OnLoad()
{
	//Audio Files
	mMenuMusic = resourceManager->LoadAudio(L"space.wav");
	mMenuMusic->Play(1.0f, 1.0f, 0.0f);

	mGUIManager->LoadSprite(L"Spaceship.png", GUIManager::SpriteOrigin::CENTRE, GUIManager::SpritePosition::CENTRE_MIDDLE, Vector2(0, 0), 0, 1);

	mGUIManager->Write(L"PEW PEW!", GUIManager::TextOrigin::CENTRE, GUIManager::TextPosition::CENTRE_TOP, Vector2(400, 250), L"AlienEncounters.spritefont", 0.0f, 1.5f, Vector4(1.0f, 0.0f, 0.0f, 1.0f));

	mGUIManager->Write(L"PLAY", GUIManager::TextOrigin::CENTRE, GUIManager::TextPosition::CENTRE_MIDDLE, Vector2(400, 0), L"AlienEncounters.spritefont", 0.0f, 0.75f, Vector4(0.75f, 0.75f, 1.0f, 1.0f));
	mGUIManager->Write(L"EXIT", GUIManager::TextOrigin::CENTRE, GUIManager::TextPosition::CENTRE_MIDDLE, Vector2(400, 100), L"AlienEncounters.spritefont", 0.0f, 0.75f, Vector4(0.75f, 0.75f, 1.0f, 1.0f));

}

/// <summary>
/// Clear up scene resources
/// </summary>
void MenuScene::OnUnload()
{
}
