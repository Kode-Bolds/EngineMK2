#pragma once
#include "OctTreeNode.h"

struct SphereCollider
{
	float radius;
	int collisionMask;
	int ignoreCollisionMask;
};