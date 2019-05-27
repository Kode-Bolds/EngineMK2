#pragma once
#include <memory>
#include <Audio.h>

class AudioSystem;

class Sound
{
protected:
	Sound();

public:
	virtual ~Sound() = default;

	virtual void Create(const AudioSystem* pAudioSystem, const std::wstring& pFilename) = 0;
	virtual void Play(float pVolume, float pPitch, float pPan) const = 0;
};