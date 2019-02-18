#pragma once
#include <memory>
#include <chrono>
#include "Scene.h"

class SceneManager
{
private:
	std::chrono::high_resolution_clock::duration mDeltaTime;
	std::chrono::high_resolution_clock::time_point mStartTime;
	std::chrono::high_resolution_clock::time_point mCurrentTime;
	std::chrono::high_resolution_clock::time_point mPreviousTime;

	Scene* mScene;
	int mFps = 0;

	SceneManager();

public:
	~SceneManager();

	const void Render();
	const void Update();
	const void LoadScene(Scene & pScene);
	const double DeltaTime() const;
	const double Time() const;
	const int Fps();

	//Singleton pattern
	//Deleted copy constructor and assignment operator so no copies of the singleton instance can be made
	SceneManager(SceneManager const&) = delete;
	SceneManager& operator=(SceneManager const&) = delete;
	static std::shared_ptr<SceneManager> Instance();
};