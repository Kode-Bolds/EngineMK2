#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <string>
#include "RenderSystem.h"

class ShaderObject
{
protected:
	ShaderObject() {};
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mVertex;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mPixel;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> mLayout;

public:
	virtual ~ShaderObject() {};

	virtual HRESULT CreateVertex(const RenderSystem* pRenderer, const std::wstring& pFilename, const std::string& pEntryPoint, const std::string& pShaderModel) = 0;
	virtual HRESULT CreatePixel(const RenderSystem* pRenderer, const std::wstring& pFilename, const std::string& pEntryPoint, const std::string& pShaderModel) = 0;
	virtual Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> VertexShader() = 0;
	virtual Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> PixelShader() = 0;
	virtual Microsoft::WRL::ComPtr<ID3D11InputLayout> InputLayout() = 0;
};