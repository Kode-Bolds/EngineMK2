#include "TransformSystem.h"

void TransformSystem::CalculateTransform(const unsigned short pEntity)
{
	Transform* t = mEcsManager->TransformComp(pEntity);
	const auto scale = KodeboldsMath::ScaleMatrix(t->scale);
	const auto translation = KodeboldsMath::TranslationMatrix(t->translation);
	const auto rotation = KodeboldsMath::RotationMatrixX(t->rotation.X)
		* KodeboldsMath::RotationMatrixY(t->rotation.Y)
		* KodeboldsMath::RotationMatrixZ(t->rotation.Z);

	t->transform = translation * rotation * scale;
}

void TransformSystem::CalculateDirections(const unsigned short pEntity)
{
	Transform* t = mEcsManager->TransformComp(pEntity);
	t->forward = KodeboldsMath::Vector4(t->transform._13, t->transform._23, t->transform._33, 1.0f).Normalise();
	t->up = KodeboldsMath::Vector4(t->transform._12, t->transform._22, t->transform._32, 1.0f).Normalise();
	t->right = KodeboldsMath::Vector4(t->transform._11, t->transform._21, t->transform._31, 1.0f).Normalise();
}

void TransformSystem::ExtractTransformations(const unsigned short pEntity)
{
	Transform* t = mEcsManager->TransformComp(pEntity);
	t->translation = KodeboldsMath::Vector4(t->transform._14, t->transform._24, t->transform._34, 1.0f);
}

TransformSystem::TransformSystem() 
	: ISystem(std::vector<int>{ ComponentType::COMPONENT_TRANSFORM })
{
	mEntities = std::vector<Entity>(mEcsManager->MaxEntities(), Entity{ -1, ComponentType::COMPONENT_NONE });
}

TransformSystem::~TransformSystem()
{
}

void TransformSystem::AssignEntity(const Entity & pEntity)
{
	//Checks if entity mask matches the transform mask
	if ((pEntity.componentMask & mMasks[0]) == mMasks[0])
	{
		//Calculate transform
		if (mEntities[pEntity.ID].ID == -1)
		{
			CalculateTransform(pEntity.ID);
			CalculateDirections(pEntity.ID);
			ExtractTransformations(pEntity.ID);
		}

		//Update entry in systems entity list
		mEntities[pEntity.ID] = pEntity;
	}
}

void TransformSystem::ReAssignEntity(const Entity & pEntity)
{
	//Checks if entity mask matches the transform mask
	if ((pEntity.componentMask & mMasks[0]) == mMasks[0])
	{
		//Calculate transform
		if (mEntities[pEntity.ID].ID == -1)
		{
			CalculateTransform(pEntity.ID);
			CalculateDirections(pEntity.ID);
			ExtractTransformations(pEntity.ID);
		}

		//If the entity matches transform mask then update entry in systems entity list
		mEntities[pEntity.ID] = pEntity;
	}
	else
	{
		//If the mask doesn't match then set ID to -1
		mEntities[pEntity.ID].ID = -1;
	}
}

void TransformSystem::Process()
{
	for (const Entity& entity : mEntities)
	{
		if (entity.ID != -1)
		{
			CalculateDirections(entity.ID);
			ExtractTransformations(entity.ID);
		}
	}
}
