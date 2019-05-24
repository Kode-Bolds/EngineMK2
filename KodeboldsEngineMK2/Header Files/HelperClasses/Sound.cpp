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

void Sound::Play(float pVolume, float pPitch, float pPan)
{
	mSound->Play(pVolume, pPitch, pPan);
}

//std::unique_ptr<DirectX::SoundEffectInstance> Sound::CreateInstance()
//{
//	auto effect = mSound->CreateInstance();
//	return effect;
//}
