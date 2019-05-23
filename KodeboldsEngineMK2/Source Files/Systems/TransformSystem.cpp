#include "TransformSystem.h"

/// <summary>
/// Constructor
/// Initialises entity vector to max entities size
/// </summary>
TransformSystem::TransformSystem()
	: ISystem(std::vector<int>{ComponentType::COMPONENT_TRANSFORM})
{
	mEntities = std::vector<Entity>(mEcsManager->MaxEntities(), Entity{ -1, ComponentType::COMPONENT_NONE });
}

/// <summary>
/// Default destructor
/// </summary>
TransformSystem::~TransformSystem()
{
}

/// <summary>
/// Assigns entity to system if the entities mask matches the system mask
/// </summary>
/// <param name="pEntity">Entity to be assigned</param>
void TransformSystem::AssignEntity(const Entity & pEntity)
{
	//Checks if entity mask matches the movement mask
	if ((pEntity.componentMask & mMasks[0]) == mMasks[0])
	{
		//Update entry in systems entity list
		mEntities[pEntity.ID] = pEntity;
		CalculateTransform(pEntity);
		CalculateDirections(pEntity);
		ExtractTransform(pEntity);
	}
}

/// <summary>
/// Re-assigns entity to system when component is removed from entity
/// </summary>
/// <param name="pEntity">Entity to re-assign</param>
void TransformSystem::ReAssignEntity(const Entity & pEntity)
{
	//Checks if entity mask matches the movement mask
	if ((pEntity.componentMask & mMasks[0]) == mMasks[0])
	{
		//If the entity matches movement mask then update entry in systems entity list
		mEntities[pEntity.ID] = pEntity;
		CalculateTransform(pEntity);
		CalculateDirections(pEntity);
		ExtractTransform(pEntity);
	}
	else
	{
		//If the mask doesn't match then set ID to -1
		mEntities[pEntity.ID].ID = -1;
	}
}

/// <summary>
/// Systems process function, core logic of system
/// Calculates entities translation, scale and rotation from the transform
/// </summary>
void TransformSystem::Process()
{
	for (const Entity& entity : mEntities)
	{
		if (entity.ID != -1)
		{
			CalculateDirections(entity);
			ExtractTransform(entity);
		}
	}
}


/// <summary>
/// Calculates the transform of a given entity based on the translation, rotation and scale of the entity
/// </summary>
/// <param name="pEntity">Given entity to calculate transform for</param>
void TransformSystem::CalculateTransform(const Entity& pEntity) const
{
	Transform* t = mEcsManager->TransformComp(pEntity.ID);
	if (t)
	{
		const auto scale = ScaleMatrix(t->scale);
		const auto translation = TranslationMatrix(t->translation);
		const auto rotation = KodeboldsMath::RotationMatrixX(t->rotation.X)
			* KodeboldsMath::RotationMatrixY(t->rotation.Y)
			* KodeboldsMath::RotationMatrixZ(t->rotation.Z);

		t->transform = translation * rotation * scale;
	}
}

void TransformSystem::CalculateDirections(const Entity& pEntity) const
{
	Transform* t = mEcsManager->TransformComp(pEntity.ID);
	if (t)
	{
		t->forward = KodeboldsMath::Vector4(t->transform._31, t->transform._32, t->transform._33, 1.0f);
		t->up = KodeboldsMath::Vector4(t->transform._21, t->transform._22, t->transform._23, 1.0f);
		t->right = KodeboldsMath::Vector4(t->transform._11, t->transform._12, t->transform._13, 1.0f);
	}
}

void TransformSystem::ExtractTransform(const Entity& pEntity) const
{
	Transform* t = mEcsManager->TransformComp(pEntity.ID);
	if (t)
	{
		t->scale = t->transform.ExtractScale();
		t->translation = t->transform.ExtractTranslation();
		t->rotation = t->transform.ExtractRotation();
	}
}
