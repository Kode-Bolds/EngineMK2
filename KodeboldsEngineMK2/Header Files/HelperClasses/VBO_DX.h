#pragma once
#include "VBO.h"

class VBO_DX :
	public VBO
{
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> mVertices{};
	Microsoft::WRL::ComPtr<ID3D11Buffer> mIndices{};

public:
	VBO_DX();
	~VBO_DX();

	HRESULT Create(const RenderSystem* pRenderer, const std::wstring& pFilename) override;
	Microsoft::WRL::ComPtr<ID3D11Buffer> Vertices() const { return mVertices; }
	Microsoft::WRL::ComPtr<ID3D11Buffer> Indices() const { return mIndices; }
};

