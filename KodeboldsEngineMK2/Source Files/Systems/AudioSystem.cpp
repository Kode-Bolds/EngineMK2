#include "AudioSystem.h"

/// <summary>
/// Constructor
/// Initialises entity vector to max entities size
/// </summary>
/// <param name="pMask">Mask for the system</param>
AudioSystem::AudioSystem(const std::vector<int>& pMasks) : ISystem(pMasks)
{
	mEntities = std::vector<Entity>(mEcsManager->MaxEntities(), Entity{ -1, ComponentType::COMPONENT_NONE });
}