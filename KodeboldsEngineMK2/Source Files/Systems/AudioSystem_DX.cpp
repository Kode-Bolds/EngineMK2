#include "AudioSystem_DX.h"

HRESULT AudioSystem_DX::Init()
{
	return E_NOTIMPL;
}

void AudioSystem_DX::Cleanup()
{
}

AudioSystem_DX::AudioSystem_DX() : AudioSystem(std::vector<int>{ComponentType::COMPONENT_AUDIO})
{
}

AudioSystem_DX::~AudioSystem_DX()
{
}

void AudioSystem_DX::AssignEntity(const Entity& pEntity)
{
	//Checks if entity mask matches the audio mask
	if ((pEntity.componentMask & mMasks[0]) == mMasks[0])
	{
		//Update entry in systems entity list
		mEntities[pEntity.ID] = pEntity;
	}
}

void AudioSystem_DX::ReAssignEntity(const Entity& pEntity)
{
	auto test = pEntity.componentMask & mMasks[0];
	//Checks if entity mask matches the renderable mask
	if ((test) == mMasks[0])
	{
		//If the entity matches audio mask then update entry in systems entity list
		mEntities[pEntity.ID] = pEntity;
	}
	else
	{
		//If the mask doesn't match then set ID to -1
		mEntities[pEntity.ID].ID = -1;
	}
}

void AudioSystem_DX::Process()
{
	for (const Entity& entity : mEntities) {
		if (entity.ID != -1)
		{
			// if the sound is active
			if (mEcsManager->AudioComp(entity.ID)->active)
			{
				// play the sound
				mEcsManager->AudioComp(entity.ID)->mSound->Play(
					mEcsManager->AudioComp(entity.ID)->volume,
					mEcsManager->AudioComp(entity.ID)->pitch, 
					mEcsManager->AudioComp(entity.ID)->pan);

				// after playing the sound, it becomes inactive unless it is set to loop
				if (mEcsManager->AudioComp(entity.ID)->loop)
				{
					mEcsManager->AudioComp(entity.ID)->active = true;
				}
				else
				{
					mEcsManager->AudioComp(entity.ID)->active = false;
				}
			}
		}
	}
}

Sound* AudioSystem_DX::LoadAudio(const Entity& pEntity)
{
	Sound* audio = nullptr;// = mResourceManager->LoadAudio(mEcsManager->AudioComp(pEntity.ID)->filename);
	return audio;
}
