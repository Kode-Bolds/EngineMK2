#pragma once
#include <string>
#include <vector>

class RenderSystem;

class ShaderObject
{
protected:
	ShaderObject() {};

public:
	virtual ~ShaderObject() {};

	virtual HRESULT CreateVertex(const RenderSystem* pRenderer, const std::wstring& pFilename, const std::string& pEntryPoint, const std::string& pShaderModel) = 0;
	virtual HRESULT CreatePixel(const RenderSystem* pRenderer, const std::wstring& pFilename, const std::string& pEntryPoint, const std::string& pShaderModel) = 0;
	virtual void Load(const RenderSystem* pRenderer) = 0;
};