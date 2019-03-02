#pragma once
#include <string>
#include <vector>

class RenderSystem;

class TextureObject
{
protected:
	TextureObject() {};

public:
	virtual ~TextureObject() {};

	virtual HRESULT Create(const RenderSystem* pRenderer, const std::vector<std::wstring>& pFilenames) = 0;
	virtual void Load(const RenderSystem* pRenderer) = 0;
};