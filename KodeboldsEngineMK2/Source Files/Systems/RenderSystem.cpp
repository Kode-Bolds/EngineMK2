#include "RenderSystem.h"

/// <summary>
/// Constructor
/// Initialises entity vector to max entities size
/// </summary>
/// <param name="pMasks">Masks for the system</param>
/// <param name="pMaxPointLights">The maximum number of point lights for the renderer</param>
/// <param name="pMaxDirLights">The maximum number of directional lights for the renderer</param>
RenderSystem::RenderSystem(const std::vector<int>& pMasks, const int pMaxPointLights, const int pMaxDirLights) : ISystem(pMasks),  mMaxPointLights(pMaxPointLights), mMaxDirLights(pMaxDirLights)
{
	mEntities = std::vector<Entity>(mEcsManager->MaxEntities(), Entity{ -1, ComponentType::COMPONENT_NONE });
}