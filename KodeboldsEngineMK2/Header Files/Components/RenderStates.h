#pragma once
#include  "CullState.h"
#include "DepthState.h"
#include "BlendState.h"

struct RenderStates
{
	CullState mCullState;
	DepthState mDepthState;
	BlendState mBlendState;
};
