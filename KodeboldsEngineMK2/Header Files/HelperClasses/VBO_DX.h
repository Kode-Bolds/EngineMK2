#pragma once
#include "VBO.h"
#include <d3d11.h>
#include "ObjLoader.h"

class RenderSystem_DX;

class VBO_DX :
	public VBO
{
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> mVertices{};
	Microsoft::WRL::ComPtr<ID3D11Buffer> mIndices{};

public:
	VBO_DX();
	~VBO_DX();

	HRESULT Create(const RenderSystem_DX* pRenderer, const std::wstring& pFilename) override;
	void Load(const RenderSystem_DX* pRenderer) const override;

	Microsoft::WRL::ComPtr<ID3D11Buffer> Vertices() const { return mVertices; }
	Microsoft::WRL::ComPtr<ID3D11Buffer> Indices() const { return mIndices; }
};

