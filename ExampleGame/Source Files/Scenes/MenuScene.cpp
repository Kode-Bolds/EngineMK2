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
		mSceneManager->LoadScene<LoadingScene>();
	}
#elif OPENGL
#endif
}

/// <summary>
/// Scene setup on load
/// </summary>
void MenuScene::OnLoad()
{
	mInputManager->CenterCursor(false);

	//Audio Files
	mMenuMusic = mEcsManager->CreateEntity();
	Audio audio{ L"Test-AnthonyBeacock-SpaceMenu.wav", true, false, 0.5f, 1.0f, 0.0f };
	mEcsManager->AddAudioComp(audio, mMenuMusic);

	// GUI
	// creates a panel that covers the screen when game is paused
	mBackgroundOverlay = mGUIManager->CreateQuadOverlay(Vector4(0.0f, 0.0f, 0.0f, 1.0f), true);

	mGUIManager->LoadSprite(L"Spaceship.png", GUIManager::SpriteOrigin::CENTRE, GUIManager::SpritePosition::CENTRE_MIDDLE, Vector2(0, 0), 0, 1, true);
	mGUIManager->Write(L"PEW PEW!", GUIManager::TextOrigin::CENTRE, GUIManager::TextPosition::CENTRE_TOP, Vector2(400, 250), L"AlienEncounters.spritefont",
		0.0f, 1.5f, Vector4(1.0f, 0.0f, 0.0f, 1.0f), true);

	mGUIManager->CreateButton(L"button.png", L"AlienEncounters.spritefont", L"PLAY", 0, 0.35f, 0.65f,
		GUIManager::ButtonOrigin::CENTRE, GUIManager::ButtonPosition::CENTRE_MIDDLE, Vector2(400, 0),
		Vector2(0, 10), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector4(1.0f, 0.0f, 0.0f, 1.0f), std::bind(&MenuScene::OnClick_PlayButton, this), true);

	mGUIManager->CreateButton(L"button.png", L"AlienEncounters.spritefont", L"EXIT", 0, 0.35f, 0.65f,
		GUIManager::ButtonOrigin::CENTRE, GUIManager::ButtonPosition::CENTRE_MIDDLE, Vector2(400, 100),
		Vector2(0, 10), Vector4(0.0f, 0.0f, 0.0f, 1.0f), Vector4(1.0f, 1.0f, 0.0f, 1.0f), std::bind(&MenuScene::OnClick_ExitButton, this), true);
}

/// <summary>
/// Clear up scene resources
/// </summary>
void MenuScene::OnUnload()
{
	// Clears GUI from previous scene
	resourceManager->mSprites.clear();
	resourceManager->mButtons.clear();
	mGUIManager->GetQuads()->clear();
	mGUIManager->GetTextVector()->clear();

	//Delete menu music entity
	mEcsManager->DestroyEntity(mMenuMusic);
}

void MenuScene::OnClick_PlayButton()
{
	mSceneManager->LoadScene<LoadingScene>();
}

void MenuScene::OnClick_ExitButton()
{
	exit(0);
}