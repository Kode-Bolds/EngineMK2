#include "CollisionCheckSystem.h"

using namespace KodeboldsMath;

/// <summary>
/// 
/// </summary>
/// <param name="pMaxOctantSize"></param>
/// <param name="pMinOctantSize"></param>
CollisionCheckSystem::CollisionCheckSystem(const int pMaxOctantSize, const int pMinOctantSize) 
	: ISystem(std::vector<int>{ComponentType::COMPONENT_BOXCOLLIDER | ComponentType::COMPONENT_TRANSFORM,
		ComponentType::COMPONENT_SPHERECOLLIDER | ComponentType::COMPONENT_TRANSFORM,
		ComponentType::COMPONENT_RAY, ComponentType::COMPONENT_TRANSFORM}),
	MAX_OCTANT_SIZE(pMaxOctantSize), MIN_OCTANT_SIZE(pMinOctantSize)
{
	ConstructTree();
}

/// <summary>
/// 
/// </summary>
CollisionCheckSystem::~CollisionCheckSystem()
{
}

/// <summary>
/// 
/// </summary>
/// <param name="pEntity"></param>
void CollisionCheckSystem::AssignEntity(const Entity & pEntity)
{
	//Checks if entity mask contains any colliders
	if ((pEntity.componentMask & mMasks[0]) == mMasks[0] || (pEntity.componentMask & mMasks[1]) == mMasks[1] || (pEntity.componentMask & mMasks[2]) == mMasks[2])
	{
		//Add entity to insertion queue
		mEntitiesToInsert.push(static_cast<unsigned short>(pEntity.ID));
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="pEntity"></param>
void CollisionCheckSystem::ReAssignEntity(const Entity & pEntity)
{
	//Checks if entity mask no longer contains any colliders
	if (!((pEntity.componentMask & mMasks[0]) == mMasks[0] || (pEntity.componentMask & mMasks[1]) == mMasks[1] || (pEntity.componentMask & mMasks[2]) == mMasks[2]))
	{
		//Add entity to removal queue
		mEntitiesToRemove.push(static_cast<unsigned short>(pEntity.ID));
	}
}

/// <summary>
/// 
/// </summary>
void CollisionCheckSystem::Process()
{
	UpdateTree();
}

/// <summary>
/// 
/// </summary>
void CollisionCheckSystem::ConstructTree()
{
	//Create initial region
	float halfSize = static_cast<float>(MAX_OCTANT_SIZE / 2);
	mOctTree = new OctTreeNode(nullptr, Vector3(-halfSize, -halfSize, -halfSize), Vector3(halfSize, halfSize, halfSize));

	//Keep splitting region until the octants reach the minimum size
	while (SplitRegion(mOctTree));
}

/// <summary>
/// 
/// </summary>
/// <param name="pRegion"></param>
bool CollisionCheckSystem::SplitRegion(OctTreeNode* const pRegion)
{
	//If this region is smaller than or equal to the minimum size then stop splitting and return true
	if (pRegion->dimensions.X <= MIN_OCTANT_SIZE)
	{
		return false;
	}

	//Get center of region
	Vector3 halfDimension = pRegion->dimensions / 2.0f;
	Vector3 center = pRegion->minBounds + halfDimension;

	//Bottom left front
	pRegion->children[0] = new OctTreeNode(pRegion, 
		pRegion->minBounds, 
		center);

	//Bottom right front
	pRegion->children[1] = new OctTreeNode(pRegion,
		Vector3(center.X, pRegion->minBounds.Y, pRegion->minBounds.Z),
		Vector3(pRegion->maxBounds.X, center.Y, center.Z));

	//Bottom right back
	pRegion->children[2] = new OctTreeNode(pRegion,
		Vector3(center.X, pRegion->minBounds.Y, center.Z),
		Vector3(pRegion->maxBounds.X, center.Y, pRegion->maxBounds.Z));

	//Bottom left back
	pRegion->children[3] = new OctTreeNode(pRegion,
		Vector3(pRegion->minBounds.X, pRegion->minBounds.Y, center.Z),
		Vector3(center.X, center.Y, pRegion->maxBounds.Z));

	//Top left front
	pRegion->children[4] = new OctTreeNode(pRegion,
		Vector3(pRegion->minBounds.X, center.Y, pRegion->minBounds.Z),
		Vector3(center.X, pRegion->maxBounds.Y, center.Z));

	//Top right front
	pRegion->children[5] = new OctTreeNode(pRegion,
		Vector3(center.X, center.Y, pRegion->minBounds.Z),
		Vector3(pRegion->maxBounds.X, pRegion->maxBounds.Y, center.Z));

	//Top right back
	pRegion->children[6] = new OctTreeNode(pRegion,
		center, 
		pRegion->maxBounds);

	//Top left back
	pRegion->children[7] = new OctTreeNode(pRegion,
		Vector3(pRegion->minBounds.X, center.Y, center.Z),
		Vector3(center.X, pRegion->maxBounds.Y, pRegion->maxBounds.Z));

	//Split all of the children of this region
	for (int i = 0; i < 8; i++)
	{
		SplitRegion(pRegion->children[i]);
	}

	return false;
}

/// <summary>
/// 
/// </summary>
void CollisionCheckSystem::UpdateTree()
{
}

/// <summary>
/// 
/// </summary>
bool CollisionCheckSystem::RaySphere()
{
	return true;
}

/// <summary>
/// 
/// </summary>
bool CollisionCheckSystem::SphereSphere()
{
	return true;
}

/// <summary>
/// 
/// </summary>
bool CollisionCheckSystem::BoxSphere()
{
	return true;
}

/// <summary>
/// 
/// </summary>
bool CollisionCheckSystem::BoxBox()
{
	return true;
}

/// <summary>
/// 
/// </summary>
bool CollisionCheckSystem::RayBox()
{
	return true;
}
