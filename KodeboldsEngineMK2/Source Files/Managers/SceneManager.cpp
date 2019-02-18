#include "SceneManager.h"

const void SceneManager::Render()
{
	mScene->Render();
}

const void SceneManager::Update()
{
	mCurrentTime = std::chrono::high_resolution_clock::now();
	mStartTime = mCurrentTime;
	mDeltaTime = mPreviousTime - mCurrentTime;

	mScene->Update();

	mPreviousTime = mCurrentTime;
}

const void SceneManager::LoadScene(Scene& pScene)
{
	// unload current scene
	mScene = nullptr; // TODO: DOES THIS CAUSE A MEMORY LEAK?

	// load new scene
	*mScene = pScene;
}

const float SceneManager::DeltaTime() const
{
	return mDeltaTime.count() * pow(10, 9); // (or 1e+9)
}

const float SceneManager::Time() const
{
	auto time = mCurrentTime - mStartTime;
	return time.count() * pow(10, 9); // (or 1e+9)
}

const int SceneManager::Fps()
{
	// TODO: Average the fps over n frames.
	mFps = 1 / DeltaTime();
	return mFps;
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

std::shared_ptr<SceneManager> SceneManager::Instance()
{
	static std::shared_ptr<SceneManager> instance{ new SceneManager };
	return instance;
}
