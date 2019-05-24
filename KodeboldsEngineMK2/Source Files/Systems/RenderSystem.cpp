#include "RenderSystem.h"

/// <summary>
/// Constructor
/// Initialises entity vector to max entities size
/// </summary>
/// <param name="pMasks">Masks for the system</param>
/// <param name="pMaxLights">The maximum number of lights for the renderer</param>
RenderSystem::RenderSystem(const std::vector<int>& pMasks, const int pMaxLights) : ISystem(pMasks),  mMaxLights(pMaxLights)
{
	mEntities = std::vector<Entity>(mEcsManager->MaxEntities(), Entity{ -1, ComponentType::COMPONENT_NONE });
}