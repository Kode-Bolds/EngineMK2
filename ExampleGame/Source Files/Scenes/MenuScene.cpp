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
	// Exit the game
	if (mInputManager->KeyDown(KEYS::KEY_ESC))
	{
		exit(0);
	}

	// play game
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
	//mMenuMusic->Play(1.0f, 1.0f, 0.0f);

	// GUI
	mGUIManager->LoadSprite(L"Spaceship.png", GUIManager::SpriteOrigin::CENTRE, GUIManager::SpritePosition::CENTRE_MIDDLE, Vector2(0, 0), 0, 1);
	mGUIManager->Write(L"PEW PEW!", GUIManager::TextOrigin::CENTRE, GUIManager::TextPosition::CENTRE_TOP, Vector2(400, 250), L"AlienEncounters.spritefont", 0.0f, 1.5f, Vector4(1.0f, 0.0f, 0.0f, 1.0f));

	mGUIManager->CreateButton(L"button.png", L"AlienEncounters.spritefont", L"PLAY", 0, 0.35f, 0.65f,
		GUIManager::ButtonOrigin::CENTRE, GUIManager::ButtonPosition::CENTRE_MIDDLE, Vector2(400, 0),
		Vector2(0, 10), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector4(1.0f, 0.0f, 0.0f, 1.0f), std::bind(&MenuScene::OnClick_PlayButton, this));

	mGUIManager->CreateButton(L"button.png", L"AlienEncounters.spritefont", L"EXIT", 0, 0.35f, 0.65f,
		GUIManager::ButtonOrigin::CENTRE, GUIManager::ButtonPosition::CENTRE_MIDDLE, Vector2(400, 100),
		Vector2(0, 10), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector4(1.0f, 1.0f, 0.0f, 1.0f), std::bind(&MenuScene::OnClick_ExitButton, this));
}

/// <summary>
/// Clear up scene resources
/// </summary>
void MenuScene::OnUnload()
{
	// Clears GUI from previous scene
	resourceManager->mSprites.clear();
	resourceManager->mButtons.clear();
	mGUIManager->mTexts.clear();
}

void MenuScene::OnClick_PlayButton()
{
	mSceneManager->LoadScene<GameScene>();
}

void MenuScene::OnClick_ExitButton()
{
	exit(0);
}