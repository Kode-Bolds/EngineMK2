#include "AudioSystem_GL.h"

AudioSystem_GL::AudioSystem_GL() : AudioSystem(std::vector<int>{ComponentType::COMPONENT_AUDIO})
{
}

AudioSystem_GL::~AudioSystem_GL()
{
}

void AudioSystem_GL::AssignEntity(const Entity & pEntity)
{
}

void AudioSystem_GL::ReAssignEntity(const Entity & pEntity)
{
}

void AudioSystem_GL::Process()
{
}

const Sound * AudioSystem_GL::LoadAudio(const Entity & pEntity)
{
	return nullptr;
}
