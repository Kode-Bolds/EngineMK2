#pragma once
#include "ECSManager.h"
#include "OctTreeNode.h"
#include "ISystem.h"
#include <queue>

class CollisionCheckSystem : public ISystem
{
private:
	std::shared_ptr<ECSManager> mEcsManager = ECSManager::Instance();

	const int MAX_OCTANT_SIZE;
	const int MIN_OCTANT_SIZE;
	OctTreeNode* mOctTree;
	std::queue<unsigned short> mEntitiesToInsert;
	std::queue<unsigned short> mEntitiesToRemove;
	std::vector<OctTreeNode*> mEntityNodeMap;

	void ConstructTree();
	void SplitRegion(OctTreeNode* const pRegion) const;
	void UpdateTree();
	void Insert(OctTreeNode* const pNode, const unsigned short pEntity);
	void HandleCollisions(OctTreeNode* const pNode, std::vector<unsigned short> pParentEntities);
	void CollisionBetweenEntities(const unsigned short pEntityA, const unsigned short pEntityB);
	bool RaySphere();
	bool SphereSphere(const KodeboldsMath::Vector3& pSpherePosA, const SphereCollider* const pSphereColliderA, const KodeboldsMath::Vector3& pSpherePosB, const SphereCollider* const pSphereColliderB);
	bool BoxSphere(const BoxCollider* const pBox, const KodeboldsMath::Vector3& pSpherePos, const SphereCollider* const pSphere);
	bool BoxBox(const BoxCollider* const pBoxA, const BoxCollider* const pBoxB);
	bool RayBox();
	bool BoxInsideRegion(OctTreeNode* const pNode, const unsigned short pEntity) const;
	bool SphereInsideRegion(OctTreeNode* const pNode, const unsigned short pEntity) const;

public:
	CollisionCheckSystem(const int pMaxOctantSize, const int pMinOctantSize);
	virtual ~CollisionCheckSystem();

	void AssignEntity(const Entity& pEntity) override;
	void ReAssignEntity(const Entity& pEntity) override;
	void Process() override;
};