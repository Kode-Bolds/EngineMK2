#pragma once
#include <windows.h>
#include <wrl.h>
#include "AudioSystem.h"

class AudioSystem_GL : public AudioSystem
{
private:
	HRESULT Init() override;
	void Cleanup() override;
public:
	explicit AudioSystem_GL(const HWND& pWindow);
	virtual ~AudioSystem_GL();

	void AssignEntity(const Entity& pEntity) override;
	void ReAssignEntity(const Entity& pEntity) override;
	void Process() override;
};
