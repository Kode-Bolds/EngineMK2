#include "RenderSystem_DX.h"

using namespace DirectX;

//NOT YET IMPLEMENTED:
//Blend states
//Depth states
//Cull states
//Texture loading
//Instance rendering


/// <summary>
/// Constructor
/// Sets component mask to contain a transform component, a geometry and a shader component
/// Initialises directX device, and cleans up directX resources if failed
/// </summary>
/// <param name="pWindow">A handle to the win32 window</param>
RenderSystem_DX::RenderSystem_DX(const HWND& pWindow)
	: RenderSystem(std::vector<int>{ ComponentType::COMPONENT_TRANSFORM | ComponentType::COMPONENT_GEOMETRY | ComponentType::COMPONENT_SHADER,
		ComponentType::COMPONENT_LIGHT,
		ComponentType::COMPONENT_CAMERA }),
	mWindow(pWindow), mActiveCamera(nullptr)
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
	mGUIManager->InititialiseGUI(mDevice.Get(), mContext.Get(), mWidth, mHeight);


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

	hr = CreateConstantBuffers();
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

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_NEVER;
	hr = mDevice->CreateDepthStencilState(&depthStencilDesc, mDepthNone.GetAddressOf());
	if (FAILED(hr))
		return hr;

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc2;
	ZeroMemory(&depthStencilDesc2, sizeof(D3D11_DEPTH_STENCIL_DESC));
	depthStencilDesc2.DepthEnable = TRUE;
	depthStencilDesc2.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc2.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
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

	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.AlphaToCoverageEnable = FALSE;
	blendDesc.IndependentBlendEnable = FALSE;

	hr = mDevice->CreateBlendState(&blendDesc, mAlphaBlend.GetAddressOf());
	if (FAILED(hr))
	{
		return hr;
	}

	D3D11_BLEND_DESC blendDesc2;
	ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));
	blendDesc2.RenderTarget[0].BlendEnable = FALSE;
	blendDesc2.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc2.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
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

	return hr;
}

/// <summary>
/// Cleans up system resources used by directx   IS THIS EVEN NEEDED???
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

	//Checks if entity mask matches the light mask
	if ((pEntity.componentMask & mMasks[1]) == mMasks[1])
	{
		//If the entity has a light component then find it in the lights
		const auto entity = find_if(mLights.begin(), mLights.end(), [&](const Entity & pEntity2) {return pEntity2.ID == pEntity.ID; });
		if (entity == mLights.end())
		{
			//If not found then add it
			mLights.push_back(pEntity);
		}
		else
		{
			//If already in the list, then update mask
			entity->componentMask = pEntity.componentMask;
		}
	}

	//If the entity is marked as a camera set it to the active camera
	if ((pEntity.componentMask & mMasks[2]) == mMasks[2])
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

	//Checks if entity mask matches the light mask
	if ((pEntity.componentMask & mMasks[1]) == mMasks[1])
	{
		//If the entity has a light component then find it in the lights
		const auto entity = find_if(mLights.begin(), mLights.end(), [&](const Entity & pEntity2) {return pEntity2.ID == pEntity.ID; });
		if (entity == mLights.end())
		{
			//If not found then add it
			mLights.push_back(pEntity);
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
		mLights.erase(remove_if(mLights.begin(), mLights.end(), [&](const Entity & pEntity2) {return pEntity2.ID == pEntity.ID; }), mLights.end());
	}

	//Checks if entity mask matches the camera mask
	if ((pEntity.componentMask & mMasks[2]) == mMasks[2])
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
	ClearView();

	//mGUIManager->Render();
	//mGUIManager->RenderText();

	/*mContext->VSSetShader(nullptr, 0, 0);
	mContext->PSSetShader(nullptr, 0, 0);
	mContext->HSSetShader(nullptr, 0, 0);
	mContext->CSSetShader(nullptr, 0, 0);
	mContext->GSSetShader(nullptr, 0, 0);

	mContext->RSSetState(nullptr);
	mContext->OMSetBlendState(nullptr, nullptr, 0);
	mContext->OMSetDepthStencilState(nullptr, 0);
*/
//mContext->OMSetRenderTargets(0, nullptr, nullptr);
//mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());

	SetCamera();
	SetLights();


	for (const Entity& entity : mEntities)
	{
		if (entity.ID != -1)
		{

			LoadGeometry(entity);
			LoadTexture(entity);
			LoadShaders(entity);

			//Set world matrix
			CalculateTransform(entity);
			mCB.mWorld = XMFLOAT4X4(reinterpret_cast<float*>(&(mEcsManager->TransformComp(entity.ID)->transform)));

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

			mGeometry->Draw(this);
		}
	}
	SwapBuffers();
}

/// <summary>
/// Clears screen to cornflower blue background
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
void RenderSystem_DX::LoadShaders(const Entity& pEntity)
{
	const Shader* s = mEcsManager->ShaderComp(pEntity.ID);
	//If shader of entity is not already in the buffers, load entities shader
	if (s->filename != mActiveShader)
	{
		const auto shader = mResourceManager->LoadShader(this, mEcsManager->ShaderComp(pEntity.ID)->filename);
		shader->Load(this);
		mActiveShader = s->filename;

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
			}
			else if (depth == DepthState::LESSEQUAL)
			{
				mContext->OMSetDepthStencilState(mDepthLessEqual.Get(), 1);
			}
		}
	}
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
}

/// <summary>
/// Sets the view and projection matrices in the constant buffer
/// </summary>
void RenderSystem_DX::SetViewProj()
{
	CalculateTransform(*mActiveCamera);

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
	if (!mLights.empty())
	{
		mCB.mLightPosition = XMFLOAT4(reinterpret_cast<float*>(&(mEcsManager->TransformComp(mLights[0].ID)->translation)));
		mCB.mLightColour = XMFLOAT4(reinterpret_cast<float*>(&(mEcsManager->LightComp(mLights[0].ID)->mColour)));
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
		if (cameraComp->active)
		{
			mActiveCamera = &camera;
		}
	}
	if (mActiveCamera)
	{
		SetViewProj();
	}
}

/// <summary>
/// Calculates the transform of a given entity based on the translation, rotation and scale of the entity
/// </summary>
/// <param name="pEntity">Given entity to calculate transform for</param>
void RenderSystem_DX::CalculateTransform(const Entity& pEntity) const
{
	Transform* t = mEcsManager->TransformComp(pEntity.ID);
	const auto scale = KodeboldsMath::ScaleMatrix(t->scale);
	const auto translation = KodeboldsMath::TranslationMatrix(t->translation);
	const auto rotation = KodeboldsMath::RotationMatrixX(t->rotation.X)
		* KodeboldsMath::RotationMatrixY(t->rotation.Y)
		* KodeboldsMath::RotationMatrixZ(t->rotation.Z);

	t->transform = scale * rotation * translation;
	t->forward = KodeboldsMath::Vector4(t->transform._31, t->transform._32, t->transform._33, 1.0f).Normalise();
	t->up = KodeboldsMath::Vector4(t->transform._21, t->transform._22, t->transform._23, 1.0f).Normalise();
	t->right = KodeboldsMath::Vector4(t->transform._11, t->transform._12, t->transform._13, 1.0f).Normalise();
}

