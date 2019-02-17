#include "RenderSystem.h"

/// <summary>
/// 
/// </summary>
RenderSystem::RenderSystem(const HWND& pWindow) : ISystem(ComponentType::COMPONENT_TRANSFORM | ComponentType::COMPONENT_GEOMETRY | ComponentType::COMPONENT_SHADER)
{
}

/// <summary>
/// 
/// </summary>
RenderSystem::~RenderSystem()
{
}

/// <summary>
/// 
/// </summary>
/// <param name="pEntity"></param>
void RenderSystem::AssignEntity(const Entity & pEntity)
{
	//Finds if an entity that matches given entities ID exists and returns it
	if ((pEntity.mComponentMask & mMask) == mMask)
	{
		//If the entity matches renderable mask then check if it is in the list 
		const auto entity = find_if(mEntities.begin(), mEntities.end(), [&](const Entity& entity) {return entity.mID == pEntity.mID; });
		if (entity == mEntities.end())
		{
			//If not found then add it
			mEntities.push_back(pEntity);
		}
	}
	else
	{
		//If the mask doesn't match then remove it (if it wasn't in the list then the remove acts as a search to confirm it is not there)
		mEntities.erase(remove_if(mEntities.begin(), mEntities.end(), [&](const Entity& entity) {return entity.mID == pEntity.mID; }), mEntities.end());
	}

	if ((pEntity.mComponentMask & ComponentType::COMPONENT_LIGHT) == ComponentType::COMPONENT_LIGHT)
	{
		//If the entity has a light component then find it in the lights
		const auto entity = find_if(mLights.begin(), mLights.end(), [&](const Entity& entity) {return entity.mID == pEntity.mID; });
		if (entity == mLights.end())
		{
			//If not found then add it
			mLights.push_back(pEntity);
		}
	}
	else
	{
		//If the mask doesn't match then remove it (if it wasn't in the list then the remove acts as a search to confirm it is not there)
		mLights.erase(remove_if(mLights.begin(), mLights.end(), [&](const Entity& entity) {return entity.mID == pEntity.mID; }), mLights.end());
	}

	//If the entity is marked as a camera set it to the active camera
	//TODO: Implement multiple cameras
	if ((pEntity.mComponentMask & ComponentType::COMPONENT_CAMERA) == ComponentType::COMPONENT_CAMERA)
	{
		mActiveCamera = &pEntity;
	}

}

void RenderSystem::Process()
{
}
