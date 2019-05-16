#include "RenderSystem.h"

/// <summary>
/// Constructor
/// Initialises entity vector with size of 200000
/// </summary>
/// <param name="pMask">Mask for the system</param>
RenderSystem::RenderSystem(const std::vector<int>& pMasks) : ISystem(pMasks)
{
	mEntities = std::vector<Entity>(mEcsManager->MaxEntities(), Entity{ -1, ComponentType::COMPONENT_NONE });
}