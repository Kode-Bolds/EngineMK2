#include "CollisionCheckSystem.h"

using namespace KodeboldsMath;

/// <summary>
/// Constructor
/// Initialises entity vector and entity node map to max entities size
/// Sets component mask that system is interested in
/// Sets min/max octant size to given size
/// Constructs oct tree
/// </summary>
/// <param name="pMaxOctantSize">Given max size of octants</param>
/// <param name="pMinOctantSize">Given min size of octants</param>
CollisionCheckSystem::CollisionCheckSystem(const int pMaxOctantSize, const int pMinOctantSize)
	: ISystem(std::vector<int>{ComponentType::COMPONENT_BOXCOLLIDER | ComponentType::COMPONENT_TRANSFORM,
		ComponentType::COMPONENT_SPHERECOLLIDER | ComponentType::COMPONENT_TRANSFORM,
		ComponentType::COMPONENT_RAY, ComponentType::COMPONENT_TRANSFORM}),
	MAX_OCTANT_SIZE(pMaxOctantSize), MIN_OCTANT_SIZE(pMinOctantSize)
{
	mEntities = std::vector<Entity>(mEcsManager->MaxEntities(), Entity{ -1, ComponentType::COMPONENT_NONE });
	mEntityNodeMap = std::vector<OctTreeNode*>(mEcsManager->MaxEntities(), nullptr);
	ConstructTree();
}

/// <summary>
/// Default destructor
/// </summary>
CollisionCheckSystem::~CollisionCheckSystem()
{
}

/// <summary>
/// Assigns entity to system if the entities mask matches the system mask
/// </summary>
/// <param name="pEntity">Entity to be assigned</param>
void CollisionCheckSystem::AssignEntity(const Entity & pEntity)
{
	//Checks if entity mask contains any colliders
	if ((pEntity.componentMask & mMasks[0]) == mMasks[0] || (pEntity.componentMask & mMasks[1]) == mMasks[1] || (pEntity.componentMask & mMasks[2]) == mMasks[2])
	{
		//Add entity to insertion queue
		if (mEntities[pEntity.ID].ID == -1)
		{
			mEntitiesToInsert.push(static_cast<unsigned short>(pEntity.ID));
			mEntities[pEntity.ID] = pEntity;
		}
	}
}

/// <summary>
/// Re-assigns entity to system when component is removed from entity
/// </summary>
/// <param name="pEntity">Entity to re-assign</param>
void CollisionCheckSystem::ReAssignEntity(const Entity & pEntity)
{
	//Checks if entity mask no longer contains any colliders
	if (!((pEntity.componentMask & mMasks[0]) == mMasks[0] || (pEntity.componentMask & mMasks[1]) == mMasks[1] || (pEntity.componentMask & mMasks[2]) == mMasks[2])
		&& mEntities[pEntity.ID].ID != -1)
	{
		//Add entity to removal queue
		mEntitiesToRemove.push(static_cast<unsigned short>(pEntity.ID));
		mEntities[pEntity.ID].ID = -1;
	}
}

/// <summary>
/// Systems process function, core logic of system
/// Updates the tree with any insertions or removals from the tree
/// Calculates all the collision checks for each node of tree
/// </summary>
void CollisionCheckSystem::Process()
{
	//Loop through all entities in the system
	for (const auto& entity : mEntities)
	{
		//If the system has been assigned this entity, the entity has a velocity component and the entity is already in the tree
		if (entity.ID != -1 && mEcsManager->VelocityComp(entity.ID) && mEntityNodeMap[entity.ID])
		{
			//If the entity has a velocity greater than 0
			if (mEcsManager->VelocityComp(entity.ID)->velocity.Magnitude() > 0)
			{
				//If the entity has a box collider
				if (mEcsManager->BoxColliderComp(entity.ID))
				{
					//If the entity is no longer within it's enclosed region, remove it and re-insert it into the tree
					if (!BoxInsideRegion(mEntityNodeMap[entity.ID], entity.ID))
					{
						mEntitiesToRemove.push(static_cast<unsigned short>(entity.ID));
						mEntitiesToInsert.push(static_cast<unsigned short>(entity.ID));
					}
				}

				//If the entity has a sphere collider
				if (mEcsManager->SphereColliderComp(entity.ID))
				{
					//If the entity is no longer within it's enclosed region, remove it and re-insert it into the tree
					if (!SphereInsideRegion(mEntityNodeMap[entity.ID], entity.ID))
					{
						mEntitiesToRemove.push(static_cast<unsigned short>(entity.ID));
						mEntitiesToInsert.push(static_cast<unsigned short>(entity.ID));
					}
				}
			}
		}

		//If the system has been assigned this entity and it has a collision component
		if (entity.ID != -1 && mEcsManager->CollisionComp(entity.ID))
		{
			//Remove collision component from previous frame
			mEcsManager->RemoveCollisionComp(entity.ID);
		}
	}

	UpdateTree();

	HandleCollisions(mOctTree, std::vector<unsigned short>{});
}

/// <summary>
/// Constructs the initial node and region of the oct tree and then splits the region into subregions
/// </summary>
void CollisionCheckSystem::ConstructTree()
{
	//Create initial region
	const float halfSize = static_cast<float>(MAX_OCTANT_SIZE) / 2;
	mOctTree = new OctTreeNode(nullptr, Vector3(-halfSize, -halfSize, -halfSize), Vector3(halfSize, halfSize, halfSize));

	//Keep splitting region until the octants reach the minimum size
	SplitRegion(mOctTree);
}

/// <summary>
/// Splits a given region contained within an oct tree node into 8 children, then recursively splits the children into 8 more until the minimum octant size is reached
/// </summary>
/// <param name="pRegion">Given region to be split</param>
void CollisionCheckSystem::SplitRegion(OctTreeNode* const pRegion) const
{
	//If this region is smaller than or equal to the minimum size then stop splitting and return true
	if (pRegion->dimensions.X <= MIN_OCTANT_SIZE)
	{
		return;
	}

	//Get center of region
	const Vector3 halfDimension = pRegion->dimensions / 2.0f;
	const Vector3 center = pRegion->minBounds + halfDimension;

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
	for (auto& i : pRegion->children)
	{
		SplitRegion(i);
	}

}

/// <summary>
/// Updates the tree with any new insertions or removals of entities
/// </summary>
void CollisionCheckSystem::UpdateTree()
{
	//Process the removal queue until it's empty
	while (!mEntitiesToRemove.empty())
	{
		//Get the node of the entity to remove from the entity node map, then remove the entity from that nodes entity list
		if (mEntityNodeMap[mEntitiesToRemove.front()])
		{
			std::vector<unsigned short>* nodeEntities = &mEntityNodeMap[mEntitiesToRemove.front()]->entities;
			nodeEntities->erase(remove(nodeEntities->begin(), nodeEntities->end(), mEntitiesToRemove.front()), nodeEntities->end());
		}

		//Set entities node to null
		mEntityNodeMap[mEntitiesToRemove.front()] = nullptr;

		mEntitiesToRemove.pop();
	}

	//Process the insertion queue until it's empty
	while (!mEntitiesToInsert.empty())
	{
		//Begin insertion of entity into oct tree
		Insert(mOctTree, mEntitiesToInsert.front());
		mEntitiesToInsert.pop();
	}
}

/// <summary>
/// Inserts a given entity into the tree, recursively calls itself on the children of the given node until the smallest enclosing region is found
/// </summary>
/// <param name="pNode">Given node to insert entity into</param>
/// <param name="pEntity">Given entity to insert</param>
void CollisionCheckSystem::Insert(OctTreeNode * const pNode, const unsigned short pEntity)
{
	//Loop through children and see if any children enclose the entities collider
	for (auto& child : pNode->children)
	{
		//If child exists
		if (child)
		{
			//If the entity has a box collider and the collider is enclosed within the region, begin looping on the childs children to see if any of those enclose the collider
			if (mEcsManager->BoxColliderComp(pEntity) && BoxInsideRegion(child, pEntity))
			{
				Insert(child, pEntity);
				return;
			}
			//If the entity has a sphere collider and the collider is enclosed within the region, begin looping on the childs children to see if any of those enclose the collider
			if (mEcsManager->SphereColliderComp(pEntity) && SphereInsideRegion(child, pEntity))
			{
				Insert(child, pEntity);
				return;
			}
		}
	}

	//Add entity to node
	pNode->entities.push_back(pEntity);
	mEntityNodeMap[pEntity] = pNode;
	return;
}

/// <summary>
/// Calculates collisions for the given node, then recursively calls itself on the children of the given node
/// </summary>
/// <param name="pNode">Given node to calculate collisions for</param>
/// <param name="pParentEntities">The entities contained within all of the parent nodes in this branch</param>
void CollisionCheckSystem::HandleCollisions(OctTreeNode * const pNode, std::vector<unsigned short> pParentEntities)
{
	//Loop through entities in this node
	for (int i = 0; i < pNode->entities.size(); i++)
	{
		//Check for collisions with other entities in this node
		for (int j = i + 1; j < pNode->entities.size(); j++)
		{
			CollisionBetweenEntities(pNode->entities[i], pNode->entities[j]);
		}

		//Check for collision with entities in the parent nodes
		for (const auto& parentEntity : pParentEntities)
		{
			CollisionBetweenEntities(pNode->entities[i], parentEntity);
		}
	}

	//Add this nodes entities to the parent entities list
	for (const auto& entity : pNode->entities)
	{
		pParentEntities.push_back(entity);
	}

	//Loop through children of node
	for (auto& child : pNode->children)
	{
		//If child exists
		if (child)
		{
			HandleCollisions(child, pParentEntities);
		}
	}

	return;
}

/// <summary>
/// Checks for a collision between two given entities and adds a collision component if a collision is found
/// </summary>
/// <param name="pEntityA">Given entity A</param>
/// <param name="pEntityB">Given entity B</param>
void CollisionCheckSystem::CollisionBetweenEntities(const unsigned short pEntityA, const unsigned short pEntityB)
{
	//If entity A has box collider
	if (mEcsManager->BoxColliderComp(pEntityA))
	{
		//If entity B has box collider
		if (mEcsManager->BoxColliderComp(pEntityB))
		{
			//If A's ignored collision mask contains B's collision mask then return as this collision will be ignored
			if ((mEcsManager->BoxColliderComp(pEntityA)->ignoreCollisionMask & mEcsManager->BoxColliderComp(pEntityB)->collisionMask)
				== mEcsManager->BoxColliderComp(pEntityB)->collisionMask)
			{
				return;
			}

			//If the entities have collided
			if (BoxBox(mEcsManager->BoxColliderComp(pEntityA), mEcsManager->BoxColliderComp(pEntityB)))
			{
				//Add collision component to entities
				if (!mEcsManager->CollisionComp(pEntityA))
					mEcsManager->AddCollisionComp(Collision{ pEntityB, mEcsManager->BoxColliderComp(pEntityB)->collisionMask }, pEntityA);

				if (!mEcsManager->CollisionComp(pEntityB))
					mEcsManager->AddCollisionComp(Collision{ pEntityA, mEcsManager->BoxColliderComp(pEntityA)->collisionMask }, pEntityB);
				return;
			}

		}

		//If entity j has sphere collider
		if (mEcsManager->SphereColliderComp(pEntityB))
		{
			//If i's ignored collision mask contains j's collision mask then return as this collision will be ignored
			if ((mEcsManager->BoxColliderComp(pEntityA)->ignoreCollisionMask & mEcsManager->SphereColliderComp(pEntityB)->collisionMask)
				== mEcsManager->SphereColliderComp(pEntityB)->collisionMask)
			{
				return;
			}

			//If the entities have collided
			if (BoxSphere(mEcsManager->BoxColliderComp(pEntityA), mEcsManager->TransformComp(pEntityB)->translation.XYZ(),
				mEcsManager->SphereColliderComp(pEntityB)))
			{
				//Add collision component to entities
				if (!mEcsManager->CollisionComp(pEntityA))
					mEcsManager->AddCollisionComp(Collision{ pEntityB, mEcsManager->SphereColliderComp(pEntityB)->collisionMask }, pEntityA);

				if (!mEcsManager->CollisionComp(pEntityB))
					mEcsManager->AddCollisionComp(Collision{ pEntityA, mEcsManager->BoxColliderComp(pEntityA)->collisionMask }, pEntityB);
				return;
			}
		}
	}

	//If entity i has sphere collider
	if (mEcsManager->SphereColliderComp(pEntityA))
	{
		//If entity j has sphere collider
		if (mEcsManager->SphereColliderComp(pEntityB))
		{
			//If i's ignored collision mask contains j's collision mask then return as this collision will be ignored
			if ((mEcsManager->SphereColliderComp(pEntityA)->ignoreCollisionMask & mEcsManager->SphereColliderComp(pEntityB)->collisionMask)
				== mEcsManager->SphereColliderComp(pEntityB)->collisionMask)
			{
				return;
			}

			//If the entities have collided
			if (SphereSphere(mEcsManager->TransformComp(pEntityA)->translation.XYZ(), mEcsManager->SphereColliderComp(pEntityA),
				mEcsManager->TransformComp(pEntityB)->translation.XYZ(), mEcsManager->SphereColliderComp(pEntityB)))
			{
				//Add collision component to entities
				if (!mEcsManager->CollisionComp(pEntityA))
					mEcsManager->AddCollisionComp(Collision{ pEntityB, mEcsManager->SphereColliderComp(pEntityB)->collisionMask }, pEntityA);

				if (!mEcsManager->CollisionComp(pEntityB))
					mEcsManager->AddCollisionComp(Collision{ pEntityA, mEcsManager->SphereColliderComp(pEntityA)->collisionMask }, pEntityB);
				return;
			}
		}
	}

	return;
}

/// <summary>
/// NOT IMPLEMENTED YET
/// </summary>
bool CollisionCheckSystem::RaySphere()
{
	return E_NOTIMPL;
}

/// <summary>
/// Calculates if two spheres are intersecting each other
/// </summary>
/// <param name="pSpherePosA">Position of sphere A</param>
/// <param name="pSphereColliderA">Collider of sphere A</param>
/// <param name="pSpherePosB">Position of sphere B</param>
/// <param name="pSphereColliderB">Collider of sphere B</param>
/// <returns>bool representing whether the spheres are intersecting each other</returns>
bool CollisionCheckSystem::SphereSphere(const Vector3& pSpherePosA, const SphereCollider* const pSphereColliderA, const Vector3& pSpherePosB, const SphereCollider* const pSphereColliderB)
{
	//If the distance between the two spheres is smaller than the combined radius of the two spheres then they are intersecting
	return ((pSpherePosA - pSpherePosB).Magnitude() < (pSphereColliderA->radius + pSphereColliderB->radius));
}

/// <summary>
/// Calculates if an AABB is intersecting with a sphere
/// </summary>
/// <param name="pBox">Box collider of the AABB</param>
/// <param name="pSpherePos">Position of the sphere</param>
/// <param name="pSphere">Sphere collider of the sphere</param>
/// <returns>bool representing whether the AABB and sphere are intersecting each other</returns>
bool CollisionCheckSystem::BoxSphere(const BoxCollider* const pBox, const Vector3& pSpherePos, const SphereCollider* const pSphere)
{
	return !(pBox->minBounds.X > (pSpherePos.X + pSphere->radius) || pBox->maxBounds.X < (pSpherePos.X - pSphere->radius) ||
		pBox->minBounds.Y >(pSpherePos.Y + pSphere->radius) || pBox->maxBounds.Y < (pSpherePos.Y - pSphere->radius) ||
		pBox->minBounds.Z >(pSpherePos.Z + pSphere->radius) || pBox->maxBounds.Z < (pSpherePos.Z - pSphere->radius));
}

/// <summary>
/// Calculates if two AABBs are interesting with each other
/// </summary>
/// <param name="pBoxA">Box collider of box A</param>
/// <param name="pBoxB">Box collider of box B</param>
/// <returns>bool representing whether the AABBs are intersecting each other</returns>
bool CollisionCheckSystem::BoxBox(const BoxCollider* const pBoxA, const BoxCollider* const pBoxB)
{
	return !(pBoxA->minBounds.X > pBoxB->maxBounds.X || pBoxA->maxBounds.X < pBoxB->minBounds.X ||
		pBoxA->minBounds.Y > pBoxB->maxBounds.Y || pBoxA->maxBounds.Y < pBoxB->minBounds.Y ||
		pBoxA->minBounds.Z > pBoxB->maxBounds.Z || pBoxA->maxBounds.Z < pBoxB->minBounds.Z);
}

/// <summary>
/// NOT IMPLEMENTED YET
/// </summary>
bool CollisionCheckSystem::RayBox()
{
	return E_NOTIMPL;
}

/// <summary>
/// Calculates whether or not an AABB is completely enclosed by a given region
/// </summary>
/// <param name="pNode">Node containing the given region</param>
/// <param name="pEntity">Entity that owns the given AABB</param>
/// <returns>bool representing whether it is enclosed or not</returns>
bool CollisionCheckSystem::BoxInsideRegion(OctTreeNode * const pNode, const unsigned short pEntity) const
{
	return (//If the min bounds of the box are greater than the min bounds of the region
		mEcsManager->BoxColliderComp(pEntity)->minBounds.X > pNode->minBounds.X &&
		mEcsManager->BoxColliderComp(pEntity)->minBounds.Y > pNode->minBounds.Y &&
		mEcsManager->BoxColliderComp(pEntity)->minBounds.Z > pNode->minBounds.Z &&

		//If the max bounds of the box are smaller than the max bounds of the region
		mEcsManager->BoxColliderComp(pEntity)->maxBounds.X < pNode->maxBounds.X &&
		mEcsManager->BoxColliderComp(pEntity)->maxBounds.Y < pNode->maxBounds.Y &&
		mEcsManager->BoxColliderComp(pEntity)->maxBounds.Z < pNode->maxBounds.Z
		);
}

/// <summary>
/// Calculates whether or not a sphere is completely enclosed by a given region
/// </summary>
/// <param name="pNode">Node containing the given region</param>
/// <param name="pEntity">Entity that owns the given sphere collider</param>
/// <returns>bool representing whether it is enclosed or not</returns>
bool CollisionCheckSystem::SphereInsideRegion(OctTreeNode * const pNode, const unsigned short pEntity) const
{
	return (//If the min bounds of the sphere are greater than the min bounds of the region
		mEcsManager->TransformComp(pEntity)->translation.X - mEcsManager->SphereColliderComp(pEntity)->radius > pNode->minBounds.X &&
		mEcsManager->TransformComp(pEntity)->translation.Y - mEcsManager->SphereColliderComp(pEntity)->radius > pNode->minBounds.Y &&
		mEcsManager->TransformComp(pEntity)->translation.Z - mEcsManager->SphereColliderComp(pEntity)->radius > pNode->minBounds.Z &&

		//If the max bounds of the sphere are smaller than the max bounds of the region
		mEcsManager->TransformComp(pEntity)->translation.X + mEcsManager->SphereColliderComp(pEntity)->radius < pNode->maxBounds.X &&
		mEcsManager->TransformComp(pEntity)->translation.Y + mEcsManager->SphereColliderComp(pEntity)->radius < pNode->maxBounds.Y &&
		mEcsManager->TransformComp(pEntity)->translation.Z + mEcsManager->SphereColliderComp(pEntity)->radius < pNode->maxBounds.Z
		);
}
