#pragma once
#include "Scene.h"
class TestScene2 :
	public Scene
{
private:

public:
	TestScene2();
	virtual ~TestScene2();

	void Update() override;
	void Render() override;
	void OnLoad() override;
};

