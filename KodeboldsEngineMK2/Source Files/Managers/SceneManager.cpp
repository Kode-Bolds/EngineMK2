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

	// Average the fps over n frames.
	mAverageDeltaTime = 0;
	for (auto i = 0; i < mLast50Frames.size() - 1; i++)
	{
		mLast50Frames[i] = mLast50Frames[i + 1];
	}
	mLast50Frames[mLast50Frames.size() - 1] = DeltaTime();

	for (auto i = 0; i < mLast50Frames.size(); i++)
	{
		mAverageDeltaTime += mLast50Frames[i];
	}
	mAverageDeltaTime = mAverageDeltaTime / mLast50Frames.size();

	mFps = 1 / mAverageDeltaTime;



	mPreviousTime = mCurrentTime;
}

const double SceneManager::DeltaTime()
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
