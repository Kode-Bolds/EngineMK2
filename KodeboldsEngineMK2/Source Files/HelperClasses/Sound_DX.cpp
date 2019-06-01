#include "Sound_DX.h"
#include "AudioSystem_DX.h"

/// <summary>
/// 
/// </summary>
Sound_DX::Sound_DX() : Sound()
{
}

/// <summary>
/// 
/// </summary>
Sound_DX::~Sound_DX()
{
}

/// <summary>
/// 
/// </summary>
/// <param name="pAudioSystem"></param>
/// <param name="pFilename"></param>
void Sound_DX::Create(const AudioSystem * pAudioSystem, const std::wstring & pFilename)
{
	DirectX::AudioEngine* engine = reinterpret_cast<const AudioSystem_DX*>(pAudioSystem)->AudioEngine();
	mSound = std::make_unique<DirectX::SoundEffect>(engine, pFilename.c_str());
}

/// <summary>
/// 
/// </summary>
/// <param name="pVolume"></param>
/// <param name="pPitch"></param>
/// <param name="pPan"></param>
void Sound_DX::Play(float pVolume, float pPitch, float pPan) const
{
	mSound->Play(pVolume, pPitch, pPan);
}
