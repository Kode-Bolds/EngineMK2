#pragma once
#include "ShaderObject.h"
#include "RenderSystem.h"
#include <d3dcompiler.h>

class ShaderObject_DX :
	public ShaderObject
{
private:
	HRESULT CompileShader(const std::wstring & pFilename, const std::string& pEntryPoint, const std::string& pShaderModel, ID3DBlob** const ppBlobOut) const;

public:
	ShaderObject_DX();
	virtual ~ShaderObject_DX();

	HRESULT CreateVertex(const RenderSystem* pRenderer, const std::wstring& pFilename, const std::string& pEntryPoint, const std::string& pShaderModel) override;
	HRESULT CreatePixel(const RenderSystem* pRenderer, const std::wstring& pFilename, const std::string& pEntryPoint, const std::string& pShaderModel) override;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> VertexShader() override;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> PixelShader() override;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> InputLayout() override;
};