#pragma once
#include <wrl.h>
#include <string>

class RenderSystem_DX;

class VBO
{
protected:
	VBO() = default;

public:
	virtual ~VBO() = default;

	virtual HRESULT Create(const RenderSystem_DX* pRenderer, const std::wstring& pFilename) = 0;
	virtual void Load(const RenderSystem_DX* pRenderer) const = 0;
	//virtual void* Vertices() const = 0;
	//virtual void* Indices() const = 0;
};
