#pragma once
#include <windows.h>
#include <wrl.h>
#include "AudioSystem.h"

class AudioSystem_GL : public AudioSystem
{
private:
public:
	explicit AudioSystem_GL();
	virtual ~AudioSystem_GL();

	void AssignEntity(const Entity& pEntity) override;
	void ReAssignEntity(const Entity& pEntity) override;
	void Process() override;

	const Sound* LoadAudio(const Entity& pEntity) override;
};
