#pragma once
#include <windows.h>
#include <d3d11shader.h>
#include <d3d11.h>
#include <d3d11_1.h>
#include <wrl.h>
#include <directxcolors.h>
#include "AudioSystem.h"

class AudioSystem_DX : public AudioSystem
{
private:
	DirectX::AUDIO_ENGINE_FLAGS eflags = DirectX::AUDIO_ENGINE_FLAGS::AudioEngine_EnvironmentalReverb | DirectX::AUDIO_ENGINE_FLAGS::AudioEngine_ReverbUseFilters;
	std::shared_ptr<DirectX::AudioEngine> mAudioEngine = std::make_shared<DirectX::AudioEngine>(eflags);

	std::wstring mActiveAudio;
public:
	explicit AudioSystem_DX();
	virtual ~AudioSystem_DX();

	void AssignEntity(const Entity& pEntity) override;
	void ReAssignEntity(const Entity& pEntity) override;
	void Process() override;

	const Sound* LoadAudio(const Entity& pEntity) override;

	std::shared_ptr<DirectX::AudioEngine> AudioEngine() const;
};
