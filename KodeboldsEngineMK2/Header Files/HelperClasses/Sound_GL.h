#pragma once
#include "Sound.h"

class AudioSystem_GL;

class Sound_GL
	: public Sound
{
private:

public:
	std::wstring filename;

	Sound_GL();
	~Sound_GL();

	void Create(const AudioSystem* pAudioSystem, const std::wstring& pFilename) override;
	void Play(float pVolume, float pPitch, float pPan) const override;
};