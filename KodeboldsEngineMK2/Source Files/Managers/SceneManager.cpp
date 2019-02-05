#include "SceneManager.h"

void SceneManager::Render()
{
	mScene->Render();
}

void SceneManager::Update()
{
	mCurrentTime = std::chrono::high_resolution_clock::now();
	mStartTime = mCurrentTime;
	mDeltaTime = mPreviousTime - mCurrentTime;

	mScene->Update();

	mPreviousTime = mCurrentTime;
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
	return mDeltaTime.count() * pow(10, 9); // (or 1e+9)
}

float SceneManager::Time()
{
	auto time = mCurrentTime - mStartTime;
	return time.count() * pow(10, 9); // (or 1e+9)
}

int SceneManager::Fps()
{
	// TODO: Average the fps over n frames.
	mFps = 1 / DeltaTime();
	return mFps;
}

SceneManager::SceneManager()
{
	if (mInstance != nullptr)
	{
		mInstance = std::make_unique<SceneManager>(this);
	}
	else
	{
		delete this;
	}
}

SceneManager::~SceneManager()
{
}
