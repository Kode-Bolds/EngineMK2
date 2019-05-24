#pragma once
#include <memory>
#include <Audio.h>

class Sound
{
private:
	std::unique_ptr<DirectX::SoundEffect> mSound;

public:
	std::wstring filename;

	Sound();
	~Sound();

	void SetSound(DirectX::AudioEngine* pAudioEngine, std::wstring pFileName);
	void Play(float pVolume, float pPitch, float pPan);
	//std::unique_ptr<DirectX::SoundEffectInstance> CreateInstance();
};