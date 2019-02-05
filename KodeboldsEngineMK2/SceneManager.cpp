#include "SceneManager.h"



void SceneManager::Render()
{
	mScene->Render();
}

void SceneManager::Update()
{
	mScene->Update();
}

void SceneManager::LoadScene(Scene& pScene)
{
	// unload current scene
	mScene = nullptr; // TODO: DOES THIS CAUSE A MEMORY LEAK?

	// load new scene
	*mScene = pScene;
}

float SceneManager::DeltaTime()
{
	return 0.0f;
}

float SceneManager::Time()
{
	return 0.0f;
}

int SceneManager::Fps()
{
	return 0;
}

SceneManager::SceneManager()
{
	if (mInstance != nullptr)
	{
		mInstance = std::make_unique<SceneManager>(this);
	}
}


SceneManager::~SceneManager()
{
}
