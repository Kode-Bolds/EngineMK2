#pragma once
#include <memory>
#include <chrono>
#include "Scene.h"
#include <array>

class SceneManager
{
private:
	std::chrono::nanoseconds mDeltaTime;
	std::chrono::high_resolution_clock::time_point mStartTime;
	std::chrono::high_resolution_clock::time_point mCurrentTime;
	std::chrono::high_resolution_clock::time_point mPreviousTime;

	std::shared_ptr<Scene> mScene;
	int mFps = 0;
	double mAverageDeltaTime = 0;
	std::array<double, 50> mLast50Frames;

	SceneManager();

public:
	~SceneManager();

	const void Render();
	const void Update();
	const double DeltaTime();
	const double Time() const;
	const int Fps();

	template <class T>
	const void LoadScene()
	{
		//Create new scene of type T
		mScene = std::make_shared<T>();

		//Set start time of scene
		mStartTime = std::chrono::high_resolution_clock::now();
	};

	//Singleton pattern
	//Deleted copy constructor and assignment operator so no copies of the singleton instance can be made
	SceneManager(SceneManager const&) = delete;
	SceneManager& operator=(SceneManager const&) = delete;
	static std::shared_ptr<SceneManager> Instance();
};