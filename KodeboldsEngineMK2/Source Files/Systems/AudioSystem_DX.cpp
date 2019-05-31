#include "AudioSystem_DX.h"

AudioSystem_DX::AudioSystem_DX() : AudioSystem(std::vector<int>{ComponentType::COMPONENT_AUDIO})
{
	eflags = DirectX::AUDIO_ENGINE_FLAGS::AudioEngine_Default;
	mAudioEngine = std::make_unique<DirectX::AudioEngine>(eflags);
}

AudioSystem_DX::~AudioSystem_DX()
{
}

/// <summary>
/// Assigns entity to system if the entities mask matches the system mask
/// </summary>
/// <param name="pEntity">Entity to be assigned</param>
void AudioSystem_DX::AssignEntity(const Entity& pEntity)
{
	//Checks if entity mask matches the audio mask
	if ((pEntity.componentMask & mMasks[0]) == mMasks[0])
	{
		//Update entry in systems entity list
		mEntities[pEntity.ID] = pEntity;
	}
}

/// <summary>
/// Re-assigns entity to system when component is removed from entity
/// </summary>
/// <param name="pEntity">Entity to re-assign</param>
/// <summary>
/// 
/// </summary>
/// <param name="pEntity"></param>
void AudioSystem_DX::ReAssignEntity(const Entity& pEntity)
{
	//Checks if entity mask matches the audio mask
	if ((pEntity.componentMask & mMasks[0]) == mMasks[0])
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

/// <summary>
/// Systems process function, core logic of system
/// Plays all the audio clips in the world
/// </summary>
void AudioSystem_DX::Process()
{
	for (const Entity& entity : mEntities) 
	{
		if (entity.ID != -1)
		{
			// if the sound is active
			if (mEcsManager->AudioComp(entity.ID)->active)
			{
				// play the sound
				LoadAudio(entity)->Play(
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

/// <summary>
/// Loads an audio file into the resource manager or retrieves an already loaded copy of the audio file
/// </summary>
/// <param name="pEntity">Entity that owns the audio component</param>
/// <returns>Handle to the Sound object containing the audio</returns>
const Sound* AudioSystem_DX::LoadAudio(const Entity& pEntity)
{
	const Sound* audio = mResourceManager->LoadAudio(this, mEcsManager->AudioComp(pEntity.ID)->filename);
	return audio;
}

/// <summary>
/// Returns a handle to the audio systems directX audio engine
/// </summary>
/// <returns>Handle to the DirectX audio engine</returns>
DirectX::AudioEngine* AudioSystem_DX::AudioEngine() const
{
	return mAudioEngine.get();
}
