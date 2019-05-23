#pragma once
#include "CollisionMask.h"

typedef struct : CollisionMask
{
	enum : int
	{
		LASER = CUSTOM_MASK,
		ASTEROID = CUSTOM_MASK << 1,
	};
}CustomCollisionMask;