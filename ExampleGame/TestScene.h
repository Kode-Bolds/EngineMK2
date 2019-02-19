#pragma once
#include "Scene.h"

class TestScene :
	public Scene
{
private:


public:
	TestScene();
	virtual ~TestScene();

	void Update() override;
	void Render() override;
	void OnLoad() override;
};

