#pragma once

struct Camera
{
	int FOV;
	int nearPlane;
	int farPlane;
	std::vector<int> activeTargets;
	bool active;
};