#pragma once
#include <string>
#include <vector>
#include <wrl.h>

class RenderSystem_DX;

class ShaderObject
{
protected:
	ShaderObject() = default;

public:
	virtual ~ShaderObject() = default;

	virtual HRESULT CreateVertex(const RenderSystem_DX* pRenderer, const std::wstring& pFilename, const std::string& pEntryPoint, const std::string& pShaderModel) = 0;
	virtual HRESULT CreatePixel(const RenderSystem_DX* pRenderer, const std::wstring& pFilename, const std::string& pEntryPoint, const std::string& pShaderModel) = 0;
	virtual void Load(const RenderSystem_DX* pRenderer) const = 0;
};