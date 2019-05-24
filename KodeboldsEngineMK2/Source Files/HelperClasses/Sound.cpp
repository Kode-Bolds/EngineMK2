#include "Sound.h"

Sound::Sound()
{
}

Sound::~Sound()
{
}

void Sound::SetSound(DirectX::AudioEngine* pAudioEngine, std::wstring pFileName)
{
	mSound = std::make_unique<DirectX::SoundEffect>(pAudioEngine, pFileName.c_str());
}

void Sound::Play()
{
	mSound->Play();
}
