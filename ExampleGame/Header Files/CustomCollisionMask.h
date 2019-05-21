#pragma once
#include "CollisionMask.h"

typedef struct : CollisionMask
{
	enum : int
	{
		LASER = CUSTOM_MASK,
		ASTEROID = CUSTOM_MASK << 1,
		FLOOR = CUSTOM_MASK << 2,
	};
}CustomCollisionMask;