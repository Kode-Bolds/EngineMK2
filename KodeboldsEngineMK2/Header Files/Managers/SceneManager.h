#pragma once
#include <memory>
#include <chrono>
#include "Scene.h"

class SceneManager final
{
private:
	std::chrono::high_resolution_clock::duration mDeltaTime;
	std::chrono::high_resolution_clock::time_point mStartTime;
	std::chrono::high_resolution_clock::time_point mCurrentTime;
	std::chrono::high_resolution_clock::time_point mPreviousTime;

	static std::unique_ptr<SceneManager> mInstance;
	std::shared_ptr<Scene> mScene;
	int mFps = 0;

	void Render();
	void Update();
	void LoadScene(Scene & pScene);
	float DeltaTime();
	float Time();
	int Fps();
public:
	SceneManager();
	~SceneManager();
	SceneManager& operator=(const SceneManager&) = delete;
	SceneManager(const SceneManager&) = delete;

	SceneManager& Instance() { return *mInstance; }
};
