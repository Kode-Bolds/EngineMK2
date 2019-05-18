#pragma once
#include <vector>
#include "Vector3.h"

struct OctTreeNode
{
	OctTreeNode* parent;
	OctTreeNode* children[8];
	std::vector<unsigned short> entities;
	KodeboldsMath::Vector3 minBounds;
	KodeboldsMath::Vector3 maxBounds;
	KodeboldsMath::Vector3 dimensions;

	OctTreeNode(OctTreeNode* pParent, KodeboldsMath::Vector3 pMinBounds, KodeboldsMath::Vector3 pMaxBounds)
	: parent(pParent), minBounds(pMinBounds), maxBounds(pMaxBounds), dimensions(pMaxBounds - pMinBounds){};
};