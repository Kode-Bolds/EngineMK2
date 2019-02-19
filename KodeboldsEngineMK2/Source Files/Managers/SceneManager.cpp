#include "SceneManager.h"

const void SceneManager::Render()
{
	mScene->Render();
}

const void SceneManager::Update()
{
	mCurrentTime = std::chrono::high_resolution_clock::now();
	mDeltaTime = mCurrentTime - mPreviousTime;

	mScene->Update();

	mPreviousTime = mCurrentTime;
}

const void SceneManager::LoadScene(Scene& pScene)
{
	//Set start time of scene
	mStartTime = std::chrono::high_resolution_clock::now();

	// unload current scene
	mScene = nullptr;

	// load new scene
	mScene = &pScene;
}

const double SceneManager::DeltaTime() const
{
	return mDeltaTime.count() / pow(10, 9); // (or 1e+9)
}

const double SceneManager::Time() const
{
	auto time = mCurrentTime - mStartTime;
	return time.count() / pow(10, 9); // (or 1e+9)
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
