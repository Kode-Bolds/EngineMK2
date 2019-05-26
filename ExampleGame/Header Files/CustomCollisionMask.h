#pragma once
#include "CollisionMask.h"

typedef struct : CollisionMask
{
	enum : int
	{
		SHIP_LASER = CUSTOM_MASK,
		ASTEROID = CUSTOM_MASK << 1,
		FLOOR = CUSTOM_MASK << 2,
		SHIP = CUSTOM_MASK << 3,
		GUN_LASER = CUSTOM_MASK << 4,
	};
}CustomCollisionMask;