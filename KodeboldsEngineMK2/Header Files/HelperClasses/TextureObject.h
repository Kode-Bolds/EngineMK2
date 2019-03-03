#pragma once
#include <string>
#include <vector>
#include <wrl.h>

class RenderSystem_DX;

class TextureObject
{
protected:
	TextureObject() = default;

public:
	virtual ~TextureObject() = default;

	virtual HRESULT Create(const RenderSystem_DX* pRenderer, const std::wstring& pFilenames) = 0;
	virtual void Load(const RenderSystem_DX* pRenderer, const int& pSlot) const = 0;
};