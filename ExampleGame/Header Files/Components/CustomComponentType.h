#pragma once
#include "ComponentType.h"

typedef struct : ComponentType
{
	enum
	{
		CUSTOM_COMPONENT_1 = CUSTOM_COMPONENT,
		CUSTOM_COMPONENT_2 = CUSTOM_COMPONENT << 1,
	};
}CustomComponentType;