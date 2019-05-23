#pragma once
#include <memory>
#include <Audio.h>

class Sound
{
private:
	std::unique_ptr<DirectX::SoundEffect> mSound;

public:
	Sound();
	~Sound();

	void SetSound(DirectX::AudioEngine* pAudioEngine, std::wstring pFileName);
	void Play();
};