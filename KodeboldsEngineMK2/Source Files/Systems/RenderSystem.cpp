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
	auto entity = find_if(mEntities.begin(), mEntities.end(), [&](const Entity& entity) {return entity.mID == pEntity.mID; });
	if (entity == mEntities.end())
	{
		if ((pEntity.mComponentMask & ComponentType::COMPONENT_CAMERA) == ComponentType::COMPONENT_CAMERA)
		{
			
		}
		if ((pEntity.mComponentMask & ComponentType::COMPONENT_LIGHT) == ComponentType::COMPONENT_LIGHT)
		{

		}
		if ((pEntity.mComponentMask & mMask) == mMask)
		{
			mEntities.push_back(pEntity);
		}
		
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="pEntityID"></param>
//void RenderSystem::RemoveEntity(const int & pEntityID)
//{
//	mEntities.erase(remove_if(mEntities.begin(), mEntities.end(), [&](const Entity& entity) {return entity.mID == pEntityID; }));
//}
