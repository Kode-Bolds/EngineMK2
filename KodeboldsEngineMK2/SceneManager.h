#pragma once
#include "Scene.h"
#include <memory>

class SceneManager final
{
private:
	static std::unique_ptr<SceneManager> mInstance;
	std::shared_ptr<Scene> mScene;
	float mDeltaTime;
	float mTime;
	int mFps;

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
