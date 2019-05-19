#pragma once
typedef struct 
{
	enum : int
	{
		NONE = 0,
		PLAYER = 1 << 1,
		ENEMY = 1 << 2,
		UI = 1 << 3,
		CUSTOM_MASK = 1 << 4,
	};
}CollisionMask;