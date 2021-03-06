#pragma once
#include "ShaderObject_DX.h"
#include "RenderSystem_DX.h"

/// <summary>
/// Compiles a shader from file
/// </summary>
/// <param name="pFilename">File name of the shader</param>
/// <param name="pEntryPoint">Entry point of the shader</param>
/// <param name="pShaderModel">Shader model of the shader</param>
/// <param name="pBlobOut">D3DBlob containing the shader data</param>
/// <returns>HRESULT status code</returns>
HRESULT ShaderObject_DX::CompileShader(const std::wstring & pFilename, const std::string& pEntryPoint, const std::string& pShaderModel, ID3DBlob** const pBlobOut) const
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
	// Setting this flag improves the shader debugging experience, but still allows 
	// the shaders to be optimized and to run exactly the way they will run in 
	// the release configuration of this program.
	dwShaderFlags |= D3DCOMPILE_DEBUG;

	// Disable optimizations to further improve shader debugging
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	ID3DBlob* errorBlob = nullptr;

	hr = D3DCompileFromFile(pFilename.c_str(), nullptr, nullptr, pEntryPoint.c_str(), pShaderModel.c_str(),
		dwShaderFlags, 0, const_cast<ID3DBlob**>(pBlobOut), &errorBlob);
	if (FAILED(hr))
	{
		if (errorBlob)
		{
			OutputDebugStringA(reinterpret_cast<const char*>(errorBlob->GetBufferPointer()));
			errorBlob->Release();
		}
		return hr;
	}
	if (errorBlob) errorBlob->Release();

	return hr;
}

/// <summary>
/// Default constructor
/// </summary>
ShaderObject_DX::ShaderObject_DX()
{
}

/// <summary>
/// Default destructor
/// </summary>
ShaderObject_DX::~ShaderObject_DX()
{
}

/// <summary>
/// Creates a vertex shader and stores it in the shader object
/// </summary>
/// <param name="pFilename">File name of the vertex shader</param>
/// <param name="pEntryPoint">Entry point of the vertex shader</param>
/// <param name="pShaderModel">Shader model of the vertex shader</param>
/// <returns>HRESULT status code</returns>
HRESULT ShaderObject_DX::CreateVertex(const RenderSystem* pRenderer, const std::wstring & pFilename, const std::string& pEntryPoint, const std::string& pShaderModel)
{
	HRESULT hr = S_OK;

	// Compiles the vertex shader
	ID3DBlob* pVSBlob = nullptr;
	hr = CompileShader(pFilename, pEntryPoint, pShaderModel, &pVSBlob);
	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Creates the vertex shader
	hr = reinterpret_cast<const RenderSystem_DX*>(pRenderer)->Device()->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, mVertex.GetAddressOf());
	if (FAILED(hr))
	{
		pVSBlob->Release();
		return hr;
	}

	// Define the shader input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layout);

	// Create the shader input layout
	hr = reinterpret_cast<const RenderSystem_DX*>(pRenderer)->Device()->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), mLayout.GetAddressOf());
	pVSBlob->Release();
	if (FAILED(hr))
	{
		return hr;
	}

	return hr;
}

/// <summary>
/// Creates a pixel shader and stores it in the shader object
/// </summary>
/// <param name="pFilename">File name of the pixel shader</param>
/// <param name="pEntryPoint">Entry point of the pixel shader</param>
/// <param name="pShaderModel">Shader model of the pixel shader</param>
/// <returns>HRESULT status code</returns>
HRESULT ShaderObject_DX::CreatePixel(const RenderSystem* pRenderer, const std::wstring & pFilename, const std::string & pEntryPoint, const std::string & pShaderModel)
{
	HRESULT hr = S_OK;

	// Compile the pixel shader
	ID3DBlob* pPSBlob = nullptr;
	hr = CompileShader(pFilename, pEntryPoint, pShaderModel, &pPSBlob);
	if (FAILED(hr))
	{
		MessageBox(nullptr,
			L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
		return hr;
	}

	// Creates the pixel shader
	hr = reinterpret_cast<const RenderSystem_DX*>(pRenderer)->Device()->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, mPixel.GetAddressOf());
	pPSBlob->Release();
	if (FAILED(hr))
	{
		return hr;
	}

	return hr;
}

/// <summary>
/// Loads the shaders contained in the shader object into the buffers of the render system
/// </summary>
/// <param name="pRenderer">Render system to assign the buffers to</param>
void ShaderObject_DX::Load(const RenderSystem * pRenderer) const 
{
	reinterpret_cast<const RenderSystem_DX*>(pRenderer)->Context()->VSSetShader(mVertex.Get(), nullptr, 0);
	reinterpret_cast<const RenderSystem_DX*>(pRenderer)->Context()->IASetInputLayout(mLayout.Get());
	reinterpret_cast<const RenderSystem_DX*>(pRenderer)->Context()->PSSetShader(mPixel.Get(), nullptr, 0);

	//reinterpret_cast<const RenderSystem_DX*>(pRenderer)->Context()->VSSetConstantBuffers(0,1, )
}

