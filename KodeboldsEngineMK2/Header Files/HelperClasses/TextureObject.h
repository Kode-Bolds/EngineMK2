#pragma once
#include <string>
#include <vector>
#include <wrl.h>

class RenderSystem;

class TextureObject
{
protected:
	TextureObject() = default;

public:
	virtual ~TextureObject() = default;

	virtual HRESULT Create(const RenderSystem* pRenderer, const std::vector<std::wstring>& pFilenames) = 0;
	virtual void Load(const RenderSystem* pRenderer) = 0;
};