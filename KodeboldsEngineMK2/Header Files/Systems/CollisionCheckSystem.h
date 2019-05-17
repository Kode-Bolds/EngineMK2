#pragma once
#include "ECSManager.h"
#include "KodeboldsMath.h"
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

	void ConstructTree();
	bool SplitRegion(OctTreeNode* const pRegion);
	void UpdateTree();
	bool RaySphere();
	bool SphereSphere();
	bool BoxSphere();
	bool BoxBox();
	bool RayBox();

public:
	CollisionCheckSystem(const int pMaxOctantSize, const int pMinOctantSize);
	virtual ~CollisionCheckSystem();

	void AssignEntity(const Entity& pEntity) override;
	void ReAssignEntity(const Entity& pEntity) override;
	void Process() override;
};