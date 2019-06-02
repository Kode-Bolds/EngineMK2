#include "RenderSystem_DX.h"

using namespace DirectX;

/// <summary>
/// Constructor
/// Sets component mask to contain a transform component, a geometry and a shader component
/// Initialises directX device, and cleans up directX resources if failed
/// </summary>
/// <param name="pWindow">A handle to the win32 window</param>
/// <param name="pMaxLights">The maximum number of lights in the render system</param>
RenderSystem_DX::RenderSystem_DX(const HWND& pWindow, const int pMaxPointLights, const int pMaxDirLights, const int pRenderTextures)
	: RenderSystem(std::vector<int>{ ComponentType::COMPONENT_TRANSFORM | ComponentType::COMPONENT_GEOMETRY | ComponentType::COMPONENT_SHADER,
		ComponentType::COMPONENT_POINTLIGHT,
		ComponentType::COMPONENT_DIRECTIONALLIGHT,
		ComponentType::COMPONENT_CAMERA },
		pMaxPointLights,
		pMaxDirLights),
	mWindow(pWindow), mActiveCamera(nullptr), mActiveGeometry(L""), mActiveShader(L""), mRenderTextureCount(pRenderTextures), mActiveRenderTarget(-1)
{
	if (FAILED(Init()))
	{
		Cleanup();
	}
}

/// <summary>
/// Default destructor
/// </summary>
RenderSystem_DX::~RenderSystem_DX()
{

}

/// <summary>
/// Initialises directx device and resources
/// </summary>
/// <returns>HRESULT status code</returns>
HRESULT RenderSystem_DX::Init()
{
	auto hr{ S_OK };

	RECT rc;
	GetClientRect(mWindow, &rc);
	mWidth = rc.right - rc.left;
	mHeight = rc.bottom - rc.top;

	hr = CreateDevice();
	if (FAILED(hr))
		return hr;


	//mGUIManager->Init(TW_DIRECT3D11, mDevice.Get(), mWidth, height);
	mGUIManager->InitialiseGUI(mDevice.Get(), mContext.Get(), mWidth, mHeight);


	hr = CreateSwapChain();
	if (FAILED(hr))
		return hr;

	hr = CreateRenderTarget();
	if (FAILED(hr))
		return hr;

	hr = CreateBlend();
	if (FAILED(hr))
		return hr;

	hr = CreateDepth();
	if (FAILED(hr))
		return hr;

	hr = CreateRasterizer();
	if (FAILED(hr))
		return hr;

	hr = CreateSampler();
	if (FAILED(hr))
		return hr;

	hr = CreateConstantBuffers();
	if (FAILED(hr))
		return hr;

	hr = CreateRenderTextures();
	if (FAILED(hr))
		return hr;

	CreateViewport();

	//Set primitive topology
	mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//improved object reporting for finding memory leaks
#ifdef _DEBUG
	Microsoft::WRL::ComPtr<ID3D11Debug> DebugDevice = nullptr;
	hr = mDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(DebugDevice.GetAddressOf()));

	hr = DebugDevice->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
#endif
	float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	const auto blendSample = 0xffffffff;
	mContext->OMSetBlendState(mNoBlend.Get(), blendFactor, blendSample);
	mContext->RSSetState(mRastNoCullState.Get());
	mContext->OMSetDepthStencilState(mDepthNone.Get(), 1);

	return hr;
}

/// <summary>
/// Creates directx device
/// </summary>
/// <returns>HRESULT status code</returns>
HRESULT RenderSystem_DX::CreateDevice()
{
	auto hr{ S_OK };

	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
	};
	const UINT numDriverTypes = ARRAYSIZE(driverTypes);

	D3D_FEATURE_LEVEL featureLevels[]
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	const auto numFeatureLevels = ARRAYSIZE(featureLevels);

	for (const auto driverType : driverTypes)
	{
		hr = D3D11CreateDevice(nullptr, driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, mDevice.GetAddressOf(), &mFeatureLevel, mContext.GetAddressOf());

		if (hr == E_INVALIDARG)
		{
			// DirectX 11.0 platforms will not recognize D3D_FEATURE_LEVEL_11_1 so we need to retry without it
			hr = D3D11CreateDevice(nullptr, driverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1,
				D3D11_SDK_VERSION, mDevice.GetAddressOf(), &mFeatureLevel, mContext.GetAddressOf());
		}

		if (SUCCEEDED(hr))
			break;
	}

	return hr;
}

/// <summary>
/// Creates swap chain for directx
/// </summary>
/// <returns>HRESULT status code</returns>
HRESULT RenderSystem_DX::CreateSwapChain()
{
	auto hr{ S_OK };

	Microsoft::WRL::ComPtr<IDXGIFactory1> dxgiFactory = nullptr;
	{
		Microsoft::WRL::ComPtr<IDXGIDevice> dxgiDevice = nullptr;
		hr = mDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(dxgiDevice.GetAddressOf()));
		if (SUCCEEDED(hr))
		{
			Microsoft::WRL::ComPtr<IDXGIAdapter> adapter = nullptr;
			hr = dxgiDevice->GetAdapter(adapter.GetAddressOf());
			if (SUCCEEDED(hr))
			{
				hr = adapter->GetParent(__uuidof(IDXGIFactory1), reinterpret_cast<void**>(dxgiFactory.GetAddressOf()));
			}
		}
	}
	if (FAILED(hr))
		return hr;

	// Create swap chain
	Microsoft::WRL::ComPtr<IDXGIFactory2> dxgiFactory2 = nullptr;
	hr = dxgiFactory->QueryInterface(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(dxgiFactory2.GetAddressOf()));
	if (dxgiFactory2)
	{
		// DirectX 11.1 or later
		hr = mDevice->QueryInterface(__uuidof(ID3D11Device1), reinterpret_cast<void**>(mDevice1.GetAddressOf()));
		if (SUCCEEDED(hr))
		{
			mContext->QueryInterface(__uuidof(ID3D11DeviceContext1), reinterpret_cast<void**>(mContext1.GetAddressOf()));
		}

		DXGI_SWAP_CHAIN_DESC1 sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.Width = mWidth;
		sd.Height = mHeight;
		sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1;

		hr = dxgiFactory2->CreateSwapChainForHwnd(mDevice.Get(), mWindow, &sd, nullptr, nullptr, mSwapChain1.GetAddressOf());
		if (SUCCEEDED(hr))
		{
			hr = mSwapChain1->QueryInterface(__uuidof(IDXGISwapChain), reinterpret_cast<void**>(mSwapChain.GetAddressOf()));
		}

	}
	else
	{
		// DirectX 11.0 systems
		DXGI_SWAP_CHAIN_DESC sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.BufferCount = 1;
		sd.BufferDesc.Width = mWidth;
		sd.BufferDesc.Height = mHeight;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.OutputWindow = mWindow;
		sd.SampleDesc.Count = 1;
		sd.SampleDesc.Quality = 0;
		sd.Windowed = TRUE;

		hr = dxgiFactory->CreateSwapChain(mDevice.Get(), &sd, mSwapChain.GetAddressOf());
	}

	dxgiFactory->MakeWindowAssociation(mWindow, DXGI_MWA_NO_ALT_ENTER);

	if (FAILED(hr))
		return hr;

	return  hr;
}

/// <summary>
/// Creates render target for directx
/// </summary>
/// <returns>HRESULT status code</returns>
HRESULT RenderSystem_DX::CreateRenderTarget()
{
	auto hr{ S_OK };

	// Create a render target view
	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer = nullptr;
	hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
	if (FAILED(hr))
		return hr;

	hr = mDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, mRenderTargetView.GetAddressOf());
	if (FAILED(hr))
		return hr;

	return hr;
}

/// <summary>
/// Creates depth stencil for diretx
/// </summary>
/// <returns>HRESULT status code</returns>
HRESULT RenderSystem_DX::CreateDepth()
{
	auto hr{ S_OK };

	// Create depth stencil texture
	D3D11_TEXTURE2D_DESC depthDesc;
	ZeroMemory(&depthDesc, sizeof(depthDesc));
	depthDesc.Width = mWidth;
	depthDesc.Height = mHeight;
	depthDesc.MipLevels = 1;
	depthDesc.ArraySize = 1;
	depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthDesc.SampleDesc.Count = 1;
	depthDesc.SampleDesc.Quality = 0;
	depthDesc.Usage = D3D11_USAGE_DEFAULT;
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthDesc.CPUAccessFlags = 0;
	depthDesc.MiscFlags = 0;
	hr = mDevice->CreateTexture2D(&depthDesc, nullptr, mDepthStencil.GetAddressOf());
	if (FAILED(hr))
		return hr;

	// Create the depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	depthStencilViewDesc.Format = depthDesc.Format;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;
	hr = mDevice->CreateDepthStencilView(mDepthStencil.Get(), &depthStencilViewDesc, mDepthStencilView.GetAddressOf());
	if (FAILED(hr))
		return hr;

	mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());

	//Depth state none
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	depthStencilDesc.StencilEnable = false;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;


	hr = mDevice->CreateDepthStencilState(&depthStencilDesc, mDepthNone.GetAddressOf());
	if (FAILED(hr))
		return hr;


	//Depth state equal

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc2;
	ZeroMemory(&depthStencilDesc2, sizeof(D3D11_DEPTH_STENCIL_DESC));
	depthStencilDesc2.DepthEnable = true;
	depthStencilDesc2.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc2.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

	depthStencilDesc2.StencilEnable = false;
	depthStencilDesc2.StencilReadMask = 0xFF;
	depthStencilDesc2.StencilWriteMask = 0xFF;
	mDevice->CreateDepthStencilState(&depthStencilDesc2, mDepthLessEqual.GetAddressOf());
	if (FAILED(hr))
		return hr;

	return hr;
}

/// <summary>
/// Creates rasteriser states
/// </summary>
/// <returns>HRESULT status code</returns>
HRESULT RenderSystem_DX::CreateRasterizer()
{
	auto hr{ S_OK };

	D3D11_RASTERIZER_DESC rasterizerWireFrameDesc;
	ZeroMemory(&rasterizerWireFrameDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterizerWireFrameDesc.FillMode = D3D11_FILL_WIREFRAME;
	rasterizerWireFrameDesc.CullMode = D3D11_CULL_NONE;

	hr = mDevice->CreateRasterizerState(&rasterizerWireFrameDesc, mRastWireframeState.GetAddressOf());
	if (FAILED(hr))
	{
		return hr;
	}

	D3D11_RASTERIZER_DESC rasterizerNoCullDesc;
	ZeroMemory(&rasterizerNoCullDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterizerNoCullDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerNoCullDesc.CullMode = D3D11_CULL_NONE;

	hr = mDevice->CreateRasterizerState(&rasterizerNoCullDesc, mRastNoCullState.GetAddressOf());
	if (FAILED(hr))
	{
		return hr;
	}

	D3D11_RASTERIZER_DESC rasterizerFrontCullDesc;
	ZeroMemory(&rasterizerFrontCullDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterizerFrontCullDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerFrontCullDesc.CullMode = D3D11_CULL_FRONT;

	hr = mDevice->CreateRasterizerState(&rasterizerFrontCullDesc, mRastFrontCullState.GetAddressOf());
	if (FAILED(hr))
	{
		return hr;
	}

	D3D11_RASTERIZER_DESC rasterizerBackCullDesc;
	ZeroMemory(&rasterizerBackCullDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterizerBackCullDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerBackCullDesc.CullMode = D3D11_CULL_BACK;

	hr = mDevice->CreateRasterizerState(&rasterizerBackCullDesc, mRastBackCullState.GetAddressOf());
	if (FAILED(hr))
	{
		return hr;
	}

	return hr;
}

/// <summary>
/// Creates blend states
/// </summary>
/// <returns>HRESULT status code</returns>
HRESULT RenderSystem_DX::CreateBlend()
{
	auto hr{ S_OK };

	//ALPHA BLENDING
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = 0x0f;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.AlphaToCoverageEnable = TRUE;
	blendDesc.IndependentBlendEnable = TRUE;

	hr = mDevice->CreateBlendState(&blendDesc, mAlphaBlend.GetAddressOf());
	if (FAILED(hr))
	{
		return hr;
	}

	//NO BLEND
	D3D11_BLEND_DESC blendDesc2;
	ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));
	blendDesc2.RenderTarget[0].BlendEnable = FALSE;
	blendDesc2.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendDesc2.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO;
	blendDesc2.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc2.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	blendDesc2.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc2.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc2.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc2.AlphaToCoverageEnable = FALSE;
	blendDesc2.IndependentBlendEnable = FALSE;

	hr = mDevice->CreateBlendState(&blendDesc2, mNoBlend.GetAddressOf());
	if (FAILED(hr))
	{
		return hr;
	}

	return hr;
}

/// <summary>
/// Creates sampler state
/// </summary>
/// <returns>HRESULT status code</returns>
HRESULT RenderSystem_DX::CreateSampler()
{
	auto hr{ S_OK };

	//Set the sampler
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc));
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	hr = mDevice->CreateSamplerState(&samplerDesc, mTexSampler.GetAddressOf());

	return hr;
}

/// <summary>
/// Creates viewport
/// </summary>
void RenderSystem_DX::CreateViewport() const
{
	// Setup the viewport
	D3D11_VIEWPORT vp;
	vp.Width = static_cast<float>(mWidth);
	vp.Height = static_cast<float>(mHeight);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	mContext->RSSetViewports(1, &vp);
}

/// <summary>
/// Creates constant buffers
/// </summary>
/// <returns>HRESULT status code</returns>
HRESULT RenderSystem_DX::CreateConstantBuffers()
{
	auto hr = S_OK;

	D3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(ConstantBuffer);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	hr = mDevice->CreateBuffer(&bufferDesc, nullptr, mConstantBuffer.GetAddressOf());
	if (FAILED(hr))
	{
		return hr;
	}
	mContext->VSSetConstantBuffers(0, 1, mConstantBuffer.GetAddressOf());
	mContext->PSSetConstantBuffers(0, 1, mConstantBuffer.GetAddressOf());

	D3D11_BUFFER_DESC bufferDesc2;
	ZeroMemory(&bufferDesc2, sizeof(bufferDesc2));
	bufferDesc2.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc2.ByteWidth = sizeof(LightingBuffer);
	bufferDesc2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc2.CPUAccessFlags = 0;
	hr = mDevice->CreateBuffer(&bufferDesc2, nullptr, mLightingBuffer.GetAddressOf());
	if (FAILED(hr))
	{
		return hr;
	}
	mContext->VSSetConstantBuffers(1, 1, mLightingBuffer.GetAddressOf());
	mContext->PSSetConstantBuffers(1, 1, mLightingBuffer.GetAddressOf());

	return hr;
}

/// <summary>
/// Create the necessary DirectX resources for rendering to texture
/// </summary>
/// <returns>HRESULT status code</returns>
HRESULT RenderSystem_DX::CreateRenderTextures()
{
	auto hr{ S_OK };

	mRenderTextures.resize(mRenderTextureCount, nullptr);
	mTextureRenderTargetViews.resize(mRenderTextureCount, nullptr);
	mRenderTextureSRVs.resize(mRenderTextureCount, nullptr);

	for (int i = 0; i < mRenderTextureCount; ++i)
	{
		D3D11_TEXTURE2D_DESC textureDesc;
		ZeroMemory(&textureDesc, sizeof(textureDesc));
		textureDesc.Width = 1920;
		textureDesc.Height = 1062;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;

		hr = mDevice->CreateTexture2D(&textureDesc, nullptr, mRenderTextures[i].GetAddressOf());
		if (FAILED(hr))
			return hr;

		D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
		ZeroMemory(&renderTargetViewDesc, sizeof(renderTargetViewDesc));
		renderTargetViewDesc.Format = textureDesc.Format;
		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetViewDesc.Texture2D.MipSlice = 0;

		hr = mDevice->CreateRenderTargetView(mRenderTextures[i].Get(), &renderTargetViewDesc, mTextureRenderTargetViews[i].GetAddressOf());
		if (FAILED(hr))
			return hr;

		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
		ZeroMemory(&shaderResourceViewDesc, sizeof(shaderResourceViewDesc));
		shaderResourceViewDesc.Format = textureDesc.Format;
		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
		shaderResourceViewDesc.Texture2D.MipLevels = 1;

		hr = mDevice->CreateShaderResourceView(mRenderTextures[i].Get(), &shaderResourceViewDesc, mRenderTextureSRVs[i].GetAddressOf());
		if (FAILED(hr))
			return hr;
	}
	return hr;
}

/// <summary>
/// Cleans up system resources used by directx
/// </summary>
void RenderSystem_DX::Cleanup()
{
	mGUIManager->Cleanup();
}

/// <summary>
/// Assigns entity to system if the entities mask matches the system mask
/// </summary>
/// <param name="pEntity">Entity to be assigned</param>
void RenderSystem_DX::AssignEntity(const Entity& pEntity)
{
	//Checks if entity mask matches the renderable mask
	if ((pEntity.componentMask & mMasks[0]) == mMasks[0])
	{
		//Update entry in systems entity list
		mEntities[pEntity.ID] = pEntity;
	}

	//Checks if entity mask matches the point light mask
	if ((pEntity.componentMask & mMasks[1]) == mMasks[1])
	{
		//If the entity has a light component then find it in the lights
		const auto entity = find_if(mPointLights.begin(), mPointLights.end(), [&](const Entity & pEntity2) {return pEntity2.ID == pEntity.ID; });
		if (entity == mPointLights.end())
		{
			//If not found then add it
			mPointLights.push_back(pEntity);
		}
		else
		{
			//If already in the list, then update mask
			entity->componentMask = pEntity.componentMask;
		}
	}

	//Checks if entity mask matches the directional light mask
	if ((pEntity.componentMask & mMasks[2]) == mMasks[2])
	{
		//If the entity has a light component then find it in the lights
		const auto entity = find_if(mDirectionalLights.begin(), mDirectionalLights.end(), [&](const Entity & pEntity2) {return pEntity2.ID == pEntity.ID; });
		if (entity == mDirectionalLights.end())
		{
			//If not found then add it
			mDirectionalLights.push_back(pEntity);
		}
		else
		{
			//If already in the list, then update mask
			entity->componentMask = pEntity.componentMask;
		}
	}

	//If the entity is marked as a camera set it to the active camera
	if ((pEntity.componentMask & mMasks[3]) == mMasks[3])
	{
		//If the entity has a light component then find it in the lights
		const auto entity = find_if(mCameras.begin(), mCameras.end(), [&](const Entity & pEntity2) {return pEntity2.ID == pEntity.ID; });
		if (entity == mCameras.end())
		{
			//If not found then add it
			mCameras.push_back(pEntity);
		}
		else
		{
			//If already in the list, then update mask
			entity->componentMask = pEntity.componentMask;
		}
	}
}

/// <summary>
/// Re-assigns entity to system when component is removed from entity
/// </summary>
/// <param name="pEntity">Entity to re-assign</param>
void RenderSystem_DX::ReAssignEntity(const Entity& pEntity)
{
	//Checks if entity mask matches the renderable mask
	if ((pEntity.componentMask & mMasks[0]) == mMasks[0])
	{
		//If the entity matches renderable mask then update entry in systems entity list
		mEntities[pEntity.ID] = pEntity;
	}
	else
	{
		//If the mask doesn't match then set ID to -1
		mEntities[pEntity.ID].ID = -1;
	}

	//Checks if entity mask matches the point light mask
	if ((pEntity.componentMask & mMasks[1]) == mMasks[1])
	{
		//If the entity has a light component then find it in the lights
		const auto entity = find_if(mPointLights.begin(), mPointLights.end(), [&](const Entity & pEntity2) {return pEntity2.ID == pEntity.ID; });
		if (entity == mPointLights.end())
		{
			//If not found then add it
			mPointLights.push_back(pEntity);
		}
		else
		{
			//If already in the list, then update mask
			entity->componentMask = pEntity.componentMask;
		}
	}
	else
	{
		//If the mask doesn't match then remove it (if it wasn't in the list then the remove acts as a search to confirm it is not there)
		mPointLights.erase(remove_if(mPointLights.begin(), mPointLights.end(), [&](const Entity & pEntity2) {return pEntity2.ID == pEntity.ID; }), mPointLights.end());
	}

	//Checks if entity mask matches the directional light mask
	if ((pEntity.componentMask & mMasks[2]) == mMasks[2])
	{
		//If the entity has a light component then find it in the lights
		const auto entity = find_if(mDirectionalLights.begin(), mDirectionalLights.end(), [&](const Entity & pEntity2) {return pEntity2.ID == pEntity.ID; });
		if (entity == mDirectionalLights.end())
		{
			//If not found then add it
			mDirectionalLights.push_back(pEntity);
		}
		else
		{
			//If already in the list, then update mask
			entity->componentMask = pEntity.componentMask;
		}
	}
	else
	{
		//If the mask doesn't match then remove it (if it wasn't in the list then the remove acts as a search to confirm it is not there)
		mDirectionalLights.erase(remove_if(mDirectionalLights.begin(), mDirectionalLights.end(), [&](const Entity & pEntity2) {return pEntity2.ID == pEntity.ID; }), mDirectionalLights.end());
	}

	//Checks if entity mask matches the camera mask
	if ((pEntity.componentMask & mMasks[3]) == mMasks[3])
	{
		//If the entity has a light component then find it in the lights
		const auto entity = find_if(mCameras.begin(), mCameras.end(), [&](const Entity & pEntity2) {return pEntity2.ID == pEntity.ID; });
		if (entity == mCameras.end())
		{
			//If not found then add it
			mCameras.push_back(pEntity);
		}
		else
		{
			//If already in the list, then update mask
			entity->componentMask = pEntity.componentMask;
		}
	}
	else
	{
		//If the mask doesn't match then remove it (if it wasn't in the list then the remove acts as a search to confirm it is not there)
		mCameras.erase(remove_if(mCameras.begin(), mCameras.end(), [&](const Entity & pEntity2) {return pEntity2.ID == pEntity.ID; }), mCameras.end());
	}
}

/// <summary>
/// Systems process function, core logic of system
/// Renders every renderable entity, as well as updating all lighting and camera data
/// </summary>
void RenderSystem_DX::Process()
{
	//Clear render targets and depth view
	ClearView();

	SetLights();

	// Need to set the constant buffers after SpriteBatch changes them
	mContext->VSSetConstantBuffers(0, 1, mConstantBuffer.GetAddressOf());
	mContext->PSSetConstantBuffers(0, 1, mConstantBuffer.GetAddressOf());
	mContext->VSSetConstantBuffers(1, 1, mLightingBuffer.GetAddressOf());
	mContext->PSSetConstantBuffers(1, 1, mLightingBuffer.GetAddressOf());

	for (int i = 0; i < mRenderTextureCount; ++i)
	{
		mActiveRenderTarget = i;
		mContext->ClearRenderTargetView(mTextureRenderTargetViews[i].Get(), DirectX::Colors::White);
		//Render to texture
		mContext->OMSetRenderTargets(1, mTextureRenderTargetViews[i].GetAddressOf(), mDepthStencilView.Get());
		Render();
		//Clear depth between renders
		mContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
	}

	mActiveRenderTarget = -1;

	//Render to window
	mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());
	Render();

	RenderGUI();
	mGUIManager->Update();

	SwapBuffers();

}

/// <summary>
/// Clears render target to black
/// </summary>
void RenderSystem_DX::ClearView() const
{
	mContext->ClearRenderTargetView(mRenderTargetView.Get(), DirectX::Colors::Black);
	mContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

/// <summary>
/// Swaps buffers in swap chain
/// </summary>
void RenderSystem_DX::SwapBuffers() const
{
	mSwapChain->Present(1, 0);
}

/// <summary>
/// Loads the geometry for the given entity into a VBO object
/// </summary>
/// <param name="pEntity">Entity to load geometry for</param>
void RenderSystem_DX::LoadGeometry(const Entity& pEntity)
{
	//If geometry of entity is not already in the buffers, load entities geometry
	if (mEcsManager->GeometryComp(pEntity.ID)->filename != mActiveGeometry)
	{
		mGeometry = mResourceManager->LoadGeometry(this, mEcsManager->GeometryComp(pEntity.ID)->filename);
		mGeometry->Load(this);
		mActiveGeometry = mEcsManager->GeometryComp(pEntity.ID)->filename;
	}
}

/// <summary>
/// Loads the shader for the given entity into a shader object
/// </summary>
/// <param name="pEntity">Entity to load shader for</param>
bool RenderSystem_DX::LoadShaders(const Entity& pEntity)
{
	const Shader* s = mEcsManager->ShaderComp(pEntity.ID);
	if (mActiveRenderTarget == -1)
	{
		if (!s->renderToScreen)
			return false;
	}
	else
	{
		const auto it = std::find(s->renderTargets.begin(), s->renderTargets.end(), mActiveRenderTarget);
		if (it == s->renderTargets.end())
			return false;
	}
	if (mActiveRenderTarget == 0)
	{
		const auto shader = mResourceManager->LoadShader(this, L"depthShader.fx");
		shader->Load(this);
		mActiveShader = L"depthShader.fx";
	}
	else
	{
		//If shader of entity is not already in the buffers, load entities shader
		if (s->filename != mActiveShader)
		{
			const auto shader = mResourceManager->LoadShader(this, s->filename);
			shader->Load(this);
			mActiveShader = s->filename;
		}
	}

	//if the render states have changed, load the appropriate ones for this shader
	const BlendState blend = s->blendState;
	if (blend != mActiveBlend)
	{
		float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		const auto blendSample = 0xffffffff;
		if (blend == BlendState::NOBLEND)
		{
			mContext->OMSetBlendState(mNoBlend.Get(), blendFactor, blendSample);

		}
		else if (blend == BlendState::ALPHABLEND)
		{
			mContext->OMSetBlendState(mAlphaBlend.Get(), blendFactor, blendSample);
			//OutputDebugString(L"ALPHA BLEND");

		}
	}

	const CullState cull = s->cullState;
	if (cull != mActiveCull)
	{
		if (cull == CullState::NONE)
		{
			mContext->RSSetState(mRastNoCullState.Get());
		}
		else if (cull == CullState::FRONT)
		{
			mContext->RSSetState(mRastFrontCullState.Get());
		}
		else if (cull == CullState::BACK)
		{
			mContext->RSSetState(mRastBackCullState.Get());
		}
		else if (cull == CullState::WIREFRAME)
		{
			mContext->RSSetState(mRastWireframeState.Get());
		}
	}

	const DepthState depth = s->depthState;
	if (depth != mActiveDepth)
	{
		if (depth == DepthState::NONE)
		{
			mContext->OMSetDepthStencilState(mDepthNone.Get(), 1);
			//OutputDebugString(L"NO DEPTH");

		}
		else if (depth == DepthState::LESSEQUAL)
		{
			mContext->OMSetDepthStencilState(mDepthLessEqual.Get(), 1);
			//OutputDebugString(L"NO DEPTH");

		}
	}
	return true;
}

/// <summary>
/// Loads the texture for the given entity into a texture object
/// </summary>
/// <param name="pEntity">Entity to load texture for</param>
void RenderSystem_DX::LoadTexture(const Entity& pEntity)
{
	if (mEcsManager->TextureComp(pEntity.ID))
	{
		//Loads diffuse texture from texture component
		auto texture = mResourceManager->LoadTexture(this, mEcsManager->TextureComp(pEntity.ID)->diffuse);
		if (texture)
		{
			texture->Load(this, 0);
		}

		//Loads normal map texture from texture component
		texture = mResourceManager->LoadTexture(this, mEcsManager->TextureComp(pEntity.ID)->normal);
		if (texture)
		{
			texture->Load(this, 1);
		}

		//Loads height map texture from texture component
		texture = mResourceManager->LoadTexture(this, mEcsManager->TextureComp(pEntity.ID)->height);
		if (texture)
		{
			texture->Load(this, 2);
		}
	}
	for (int i = 0; i < mRenderTextureCount; ++i)
	{
		if (mActiveRenderTarget != i)
		{
			mContext->PSSetShaderResources(3 + i, 1, mRenderTextureSRVs[i].GetAddressOf());
		}
	}
}

/// <summary>
/// Sets the view and projection matrices in the constant buffer
/// </summary>
void RenderSystem_DX::SetViewProj()
{
	//Calculates the view matrix and sets it in the constant buffer
	const XMFLOAT4 position(reinterpret_cast<float*>(&(mEcsManager->TransformComp(mActiveCamera->ID)->translation)));
	mCB.mCameraPosition = position;

	KodeboldsMath::Vector4 lookAtV = mEcsManager->TransformComp(mActiveCamera->ID)->translation + mEcsManager->TransformComp(mActiveCamera->ID)->forward;
	const XMFLOAT4 lookAt(reinterpret_cast<float*>(&(lookAtV)));
	const XMFLOAT4 up(reinterpret_cast<float*>(&(mEcsManager->TransformComp(mActiveCamera->ID)->up)));

	const XMVECTOR posVec = XMLoadFloat4(&position);
	const XMVECTOR lookAtVec = XMLoadFloat4(&lookAt);
	const XMVECTOR upVec = XMLoadFloat4(&up);

	XMStoreFloat4x4(&mCB.mView, XMMatrixTranspose(XMMatrixLookAtLH(posVec, lookAtVec, upVec)));

	//Calculates the projection matrix and sets it in the constant buffer
	const float fov = XMConvertToRadians(mEcsManager->CameraComp(mActiveCamera->ID)->FOV);
	const float aspectRatio = static_cast<float>(mWidth) / static_cast<float>(mHeight);
	const float nearClip = mEcsManager->CameraComp(mActiveCamera->ID)->nearPlane;
	const float farClip = mEcsManager->CameraComp(mActiveCamera->ID)->farPlane;

	XMStoreFloat4x4(&mCB.mProj, XMMatrixTranspose(XMMatrixPerspectiveFovLH(fov, aspectRatio, nearClip, farClip)));
}

/// <summary>
/// Sets the light position and colour in the constant buffer
/// </summary>
void RenderSystem_DX::SetLights()
{
	if (mDirectionalLights.size() > mMaxDirLights)
	{
		mLightCB.numDirLights = mMaxDirLights;
	}
	else
	{
		mLightCB.numDirLights = mDirectionalLights.size();
	}

	for (int i = 0; i < mLightCB.numDirLights; ++i)
	{
		const auto dlComp = mEcsManager->DirectionalLightComp(mDirectionalLights[i].ID);

		//Calculates the view matrix and sets it in the constant buffer
		const XMFLOAT4 position(reinterpret_cast<float*>(&(mEcsManager->TransformComp(mDirectionalLights[i].ID)->translation)));

		KodeboldsMath::Vector4 lookAtV = mEcsManager->TransformComp(mDirectionalLights[i].ID)->translation - dlComp->mDirection;
		const XMFLOAT4 lookAt(reinterpret_cast<float*>(&(lookAtV)));
		const XMFLOAT4 up(reinterpret_cast<float*>(&(mEcsManager->TransformComp(mDirectionalLights[i].ID)->up)));

		const XMVECTOR posVec = XMLoadFloat4(&position);
		const XMVECTOR lookAtVec = XMLoadFloat4(&lookAt);
		const XMVECTOR upVec = XMLoadFloat4(&up);

		XMFLOAT4X4 view;
		XMStoreFloat4x4(&view, XMMatrixTranspose(XMMatrixLookAtLH(posVec, lookAtVec, upVec)));

		//Calculates the projection matrix and sets it in the constant buffer
		const float fov = XMConvertToRadians(mEcsManager->CameraComp(mDirectionalLights[i].ID)->FOV);
		const float aspectRatio = static_cast<float>(mWidth) / static_cast<float>(mHeight);
		const float nearClip = mEcsManager->CameraComp(mDirectionalLights[i].ID)->nearPlane;
		const float farClip = mEcsManager->CameraComp(mDirectionalLights[i].ID)->farPlane;

		XMFLOAT4X4 proj;
		XMStoreFloat4x4(&proj, XMMatrixTranspose(XMMatrixPerspectiveFovLH(fov, aspectRatio, nearClip, farClip)));

		const DirectionalLightCB dl{
			XMFLOAT3(reinterpret_cast<float*>(&dlComp->mDirection)),
			1.0f,
			XMFLOAT4(reinterpret_cast<float*>(&dlComp->mColour)),
			view,
			proj
		};
		mLightCB.dirLights[i] = dl;
	}

	if (mPointLights.size() > mMaxPointLights)
	{
		mLightCB.numPointLights = mMaxPointLights;
	}
	else
	{
		mLightCB.numPointLights = mPointLights.size();
	}

	for (int i = 0; i < mLightCB.numPointLights; ++i)
	{
		if (const auto plComp = mEcsManager->PointLightComp(mPointLights[i].ID))
		{
			const PointLightCB pl{
	XMFLOAT4(reinterpret_cast<float*>(&(mEcsManager->TransformComp(mPointLights[i].ID)->translation))),
	XMFLOAT4(reinterpret_cast<float*>(&plComp->mColour)),
	plComp->mRange,
	XMFLOAT3(0,0,0)
			};
			mLightCB.pointLights[i] = pl;
		}
	}
}

/// <summary>
/// Sets the currently active camera based on the active bool in the camera component (no support for multiple active cameras)
/// </summary>
void RenderSystem_DX::SetCamera()
{
	for (const auto& camera : mCameras)
	{
		const auto cameraComp = mEcsManager->CameraComp(camera.ID);
		if (mActiveRenderTarget == -1 && cameraComp->active)
		{
			mActiveCamera = &camera;
		}
		else
		{
			auto it = std::find(cameraComp->activeTargets.begin(), cameraComp->activeTargets.end(), mActiveRenderTarget);
			if (it != cameraComp->activeTargets.end())
			{
				mActiveCamera = &camera;
			}
		}
	}
	if (mActiveCamera)
	{
		SetViewProj();
	}
}

/// <summary>
/// Renders the scene
/// </summary>
void RenderSystem_DX::Render()
{
	SetCamera();
	//Load everything necessary and draw each entity
	for (const Entity& entity : mEntities)
	{
		if (entity.ID != -1)
		{
			if (!LoadShaders(entity))
				continue;
			LoadGeometry(entity);
			LoadTexture(entity);

			//Set world matrix
			mCB.mWorld = XMFLOAT4X4(reinterpret_cast<float*>(&(mEcsManager->TransformComp(entity.ID)->transform)));

			//Set time
			mCB.time = static_cast<float>(mSceneManager->Time());

			//Set colour if there is a colour component attached
			if ((entity.componentMask & ComponentType::COMPONENT_COLOUR) == ComponentType::COMPONENT_COLOUR)
			{
				mCB.mColour = XMFLOAT4(reinterpret_cast<float*>(&(mEcsManager->ColourComp(entity.ID)->mColour)));
			}
			else
			{
				mCB.mColour = XMFLOAT4(0, 0, 0, 0);
			}

			//Update constant buffer
			mContext->UpdateSubresource(mConstantBuffer.Get(), 0, nullptr, &mCB, 0, 0);
			mContext->UpdateSubresource(mLightingBuffer.Get(), 0, nullptr, &mLightCB, 0, 0);

			mGeometry->Draw(this);
		}
	}
}

/// <summary>
/// Renders the GUI
/// </summary>
void RenderSystem_DX::RenderGUI() const
{
#pragma region PRIMITIVE SHAPES
	//mContext->OMSetBlendState(mGUIManager->GetCommonStates()->Opaque(), nullptr, 0xFFFFFFFF);
	//mContext->OMSetDepthStencilState(mGUIManager->GetCommonStates()->DepthNone(), 0);
	//mContext->RSSetState(mGUIManager->GetCommonStates()->CullNone());
	mGUIManager->GetBasicEffect()->Apply(mContext.Get());
	//mContext->IASetInputLayout(mGUIManager->GetInputLayout().Get());

	mGUIManager->GetPrimitiveBatch()->Begin();

	// QUADS
	auto quads = *mGUIManager->GetQuads();
	for (int i = 0; i < quads.size(); i++)
	{
		if (quads[i].mIsVisible)
		{
			mGUIManager->GetPrimitiveBatch()->DrawQuad(quads[i].mTopLeftPoint, quads[i].mTopRightPoint, quads[i].mBottomRightPoint, quads[i].mBottomLeftPoint);
		}
	}
	mGUIManager->GetPrimitiveBatch()->End();
#pragma endregion
	//ID3D11DepthStencilState* ppDepthStencilState = nullptr;
	//mContext->OMGetDepthStencilState(&ppDepthStencilState, );

	// standard sprites
	mGUIManager->GetSpriteBatch()->Begin(DirectX::SpriteSortMode_Deferred, mGUIManager->GetCommonStates()->NonPremultiplied()/*, nullptr, nullptr, nullptr, nullptr*/);
	//mGUIManager->GetSpriteBatch()->Begin(DirectX::SpriteSortMode_Deferred, mGUIManager->GetCommonStates()->NonPremultiplied(), mTexSampler.Get(), mDepthLessEqual.Get(), mRastNoCullState.Get(), nullptr, XMMatrixIdentity() /*, nullptr, nullptr, nullptr, nullptr*/);
	for (int i = 0; i < mResourceManager->mSprites.size(); i++)
	{
		auto sprite = mResourceManager->mSprites[i].second;

		if (sprite.mIsVisible)
		{
			mGUIManager->GetSpriteBatch()->Draw(sprite.mTexture.Get(), sprite.mPosition, nullptr, DirectX::Colors::White, sprite.mRotation, sprite.mOrigin, sprite.mScale);
		}
	}
	//mGUIManager->GetSpriteBatch()->End();

	// standard text
	//mGUIManager->GetSpriteBatch()->Begin(DirectX::SpriteSortMode_Deferred, mGUIManager->GetCommonStates()->NonPremultiplied()/*, nullptr, nullptr, nullptr, nullptr*/);

	auto test = *mGUIManager->GetTextVector();
	auto test2 = *mGUIManager->GetFontsVector();
	for (int i = 0; i < test.size(); i++)
	{
		if (test[i].mIsVisible)
		{
			DirectX::XMVECTOR origin = DirectX::XMVectorSet(test[i].mOrigin.x, test[i].mOrigin.y, 0, 0);
			DirectX::XMVECTOR position = DirectX::XMVectorSet(test[i].mPosition.x, test[i].mPosition.y, 0, 0);
			DirectX::XMVECTOR colour = DirectX::XMVectorSet(test[i].mColour.x, test[i].mColour.y, test[i].mColour.z, test[i].mColour.w);

			test2[i]->DrawString(mGUIManager->GetSpriteBatch().get(), test[i].mText, position, colour, test[i].mRotation, origin, test[i].mScale);
		}
	}
	//mGUIManager->GetSpriteBatch()->End();

	// buttons
	//mGUIManager->GetSpriteBatch()->Begin(DirectX::SpriteSortMode_Deferred, mGUIManager->GetCommonStates()->NonPremultiplied()/*, nullptr, nullptr, nullptr, nullptr*/);
	for (int i = 0; i < mResourceManager->mButtons.size(); i++)
	{
		// sprites
		auto sprite = mResourceManager->mButtons[i].second.mSprite;

		if (sprite.mIsVisible)
		{
			mGUIManager->GetSpriteBatch()->Draw(sprite.mTexture.Get(), sprite.mPosition, nullptr, DirectX::Colors::White, sprite.mRotation, sprite.mOrigin, sprite.mScale);
		}

		// text
		auto text = mResourceManager->mButtons[i].second.mText;

		if (text.mIsVisible)
		{
			DirectX::XMVECTOR origin = DirectX::XMVectorSet(text.mOrigin.x, text.mOrigin.y, 0, 0);
			DirectX::XMVECTOR position = DirectX::XMVectorSet(text.mPosition.x, text.mPosition.y, 0, 0);
			DirectX::XMVECTOR colour = DirectX::XMVectorSet(text.mColour.x, text.mColour.y, text.mColour.z, text.mColour.w);

			test2[i]->DrawString(mGUIManager->GetSpriteBatch().get(), text.mText, position, colour, text.mRotation, origin, text.mScale);
		}
	}
	mGUIManager->GetSpriteBatch()->End();
}
