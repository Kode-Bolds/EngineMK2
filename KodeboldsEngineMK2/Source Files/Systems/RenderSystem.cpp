#include "RenderSystem.h"

/// <summary>
/// 
/// </summary>
/// <param name="pWindow"></param>
RenderSystem::RenderSystem(const HWND& pWindow) : ISystem(ComponentType::COMPONENT_TRANSFORM | ComponentType::COMPONENT_GEOMETRY | ComponentType::COMPONENT_SHADER), 
	mWindow(pWindow), mActiveCamera(nullptr)
{
	if (FAILED(Init()))
	{
		Cleanup();
	}
}

/// <summary>
/// 
/// </summary>
RenderSystem::~RenderSystem() = default;

/// <summary>
/// 
/// </summary>
/// <returns></returns>
HRESULT RenderSystem::Init()
{
	auto hr{ S_OK };

	RECT rc;
	GetClientRect(mWindow, &rc);
	mWidth = rc.right - rc.left;
	mHeight = rc.bottom - rc.top;

	hr = CreateDevice();
	if (FAILED(hr))
		return hr;

	hr = CreateSwapChain();
	if (FAILED(hr))
		return hr;

	hr = CreateRenderTarget();
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

	CreateViewport();

	// Set primitive topology
	mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//improved object reporting for finding memory leaks
	//#ifdef _DEBUG
	//	Microsoft::WRL::ComPtr<ID3D11Debug> DebugDevice = nullptr;
	//	hr = mDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(DebugDevice.GetAddressOf()));
	//
	//	hr = DebugDevice->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	//#endif

	//Create constant buffers
	CreateConstantBuffers();

	return hr;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
HRESULT RenderSystem::CreateDevice()
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
/// 
/// </summary>
/// <returns></returns>
HRESULT RenderSystem::CreateSwapChain()
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

	// Note this tutorial doesn't handle full-screen swapchains so we block the ALT+ENTER shortcut
	dxgiFactory->MakeWindowAssociation(mWindow, DXGI_MWA_NO_ALT_ENTER);

	if (FAILED(hr))
		return hr;

	return  hr;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
HRESULT RenderSystem::CreateRenderTarget()
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
/// 
/// </summary>
/// <returns></returns>
HRESULT RenderSystem::CreateDepth()
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

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	hr = mDevice->CreateDepthStencilState(&depthStencilDesc, mDepthStencilState.GetAddressOf());
	if (FAILED(hr))
		return hr;

	return hr;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
HRESULT RenderSystem::CreateRasterizer()
{
	auto hr{ S_OK };

	D3D11_RASTERIZER_DESC rasterizerDesc;
	ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_NONE;

	hr = mDevice->CreateRasterizerState(&rasterizerDesc, mDefaultRasterizerState.GetAddressOf());

	return hr;
}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
HRESULT RenderSystem::CreateSampler()
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
/// 
/// </summary>
void RenderSystem::CreateViewport() const
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

HRESULT RenderSystem::CreateConstantBuffers()
{
	return E_NOTIMPL;
}

/// <summary>
/// 
/// </summary>
void RenderSystem::Cleanup()
{
}

/// <summary>
/// 
/// </summary>
/// <param name="pEntity"></param>
void RenderSystem::AssignEntity(const Entity & pEntity)
{
	//Finds if an entity that matches given entities ID exists and returns it
	if ((pEntity.mComponentMask & mMask) == mMask)
	{
		//If the entity matches renderable mask then check if it is in the list 
		const auto entity = find_if(mEntities.begin(), mEntities.end(), [&](const Entity& entity) {return entity.mID == pEntity.mID; });
		if (entity == mEntities.end())
		{
			//If not found then add it
			mEntities.push_back(pEntity);
		}
		else
		{
			//if already in the list, then update mask
			entity->mComponentMask = pEntity.mComponentMask;
		}
	}
	else
	{
		//If the mask doesn't match then remove it (if it wasn't in the list then the remove acts as a search to confirm it is not there)
		mEntities.erase(remove_if(mEntities.begin(), mEntities.end(), [&](const Entity& entity) {return entity.mID == pEntity.mID; }), mEntities.end());
	}

	if ((pEntity.mComponentMask & ComponentType::COMPONENT_LIGHT) == ComponentType::COMPONENT_LIGHT)
	{
		//If the entity has a light component then find it in the lights
		const auto entity = find_if(mLights.begin(), mLights.end(), [&](const Entity& entity) {return entity.mID == pEntity.mID; });
		if (entity == mLights.end())
		{
			//If not found then add it
			mLights.push_back(pEntity);
		}
		else
		{
			//if already in the list, then update mask
			entity->mComponentMask = pEntity.mComponentMask;
		}
	}
	else
	{
		//If the mask doesn't match then remove it (if it wasn't in the list then the remove acts as a search to confirm it is not there)
		mLights.erase(remove_if(mLights.begin(), mLights.end(), [&](const Entity& entity) {return entity.mID == pEntity.mID; }), mLights.end());
	}

	//If the entity is marked as a camera set it to the active camera
	//TODO: Implement multiple cameras
	if ((pEntity.mComponentMask & ComponentType::COMPONENT_CAMERA) == ComponentType::COMPONENT_CAMERA)
	{
		mActiveCamera = &pEntity;

		//if already in the list, then update mask
		//mActiveCamera->mComponentMask = pEntity.mComponentMask;
	}

}

/// <summary>
/// 
/// </summary>
void RenderSystem::Process()
{
	ClearView();
	for (const Entity& entity : mEntities)
	{
		LoadGeometry(entity);

	}

	SwapBuffers();
}


void RenderSystem::ClearView() const
{
	mContext->ClearRenderTargetView(mRenderTargetView.Get(), DirectX::Colors::CornflowerBlue);
	mContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void RenderSystem::SwapBuffers() const
{
	mSwapChain->Present(1, 0);
}

/// <summary>
/// Sets the given entities geometry buffers as the active buffers (does not create buffers that do not exist)
/// </summary>
/// <param name="pEntity"></param>
void RenderSystem::LoadGeometry(const Entity& pEntity) const
{
	auto geometry = mResourceManager->LoadGeometry(mEcsManager->GeometryComp(pEntity.mID)->mFilename);
	// Set vertex buffer
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0;
	mContext->IASetVertexBuffers(0, 1, geometry.first.GetAddressOf(), &stride, &offset);

	// Set index buffer
	mContext->IASetIndexBuffer(geometry.second.Get(), DXGI_FORMAT_R16_UINT, 0);
}

