#pragma once
#include "Sound.h"

class AudioSystem_DX;

class Sound_DX 
	: public Sound
{
private:
	std::unique_ptr<DirectX::SoundEffect> mSound;

public:
	std::wstring filename;

	Sound_DX();
	~Sound_DX();

	void Create(const AudioSystem* pAudioSystem, const std::wstring& pFilename) override;
	void Play(float pVolume, float pPitch, float pPan) const override;
};