#pragma once
#include <wrl.h>
#include <string>

class RenderSystem;

class VBO
{
protected:
	VBO();

public:
	virtual ~VBO();

	virtual HRESULT Create(const RenderSystem* pRenderer, const std::wstring& pFilename) = 0;
	virtual void Load(const RenderSystem* pRenderer) const = 0;
	//virtual void* Vertices() const = 0;
	//virtual void* Indices() const = 0;
};
