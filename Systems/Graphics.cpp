#include "stdafx.h"
#include "Graphics.h"

Graphics::Graphics()
{
	EnumerateAdapters();
	CreateSwapChain();
}

Graphics::~Graphics()
{
}

void Graphics::Begin()
{
	SetViewport();
	SetBackBufferToRTV();
}


void Graphics::End()
{
	HRESULT hr = swapChain->Present(1, 0);
	CHECK(hr);
}

void Graphics::Resize(const float& width, const float& height)
{	
	DeleteSuface();
	{
		HRESULT hr = swapChain->ResizeBuffers
		(
			0,
			(UINT)width,
			(UINT)height,
			DXGI_FORMAT_UNKNOWN,
			0
		);
		CHECK(hr);
	}
	CreateRenderTargetView();	
	SetViewport(width, height);
	//SetBackBufferToRTV();

	cout << width << " X " << height << '\n';
}

void Graphics::SetViewport(const float& width, const float& height)
{
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
}

void Graphics::SetViewport()
{
	deviceContext->RSSetViewports(1, &viewport);
}

void Graphics::SetBackBufferToRTV()
{
	deviceContext->OMSetRenderTargets(1, rtv.GetAddressOf(), nullptr);
	deviceContext->ClearRenderTargetView(rtv.Get(), clearColor);
}

void Graphics::EnumerateAdapters()
{
	ComPtr<IDXGIFactory1> factory;
	if (FAILED(CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&factory)))
		return;

	UINT index = 0;
	while (true)
	{
		ComPtr<IDXGIAdapter1> adapter;
		HRESULT hr = factory->EnumAdapters1(index, &adapter);

		if (hr == DXGI_ERROR_NOT_FOUND)
			break;

		CHECK(hr);

		auto adapterInfo = make_shared<D3DEnumAdapterInfo>();
		adapterInfo->adapterOrdinal = index;

		adapter->GetDesc1(&adapterInfo->adapterDesc);
		adapterInfo->adapter = adapter;

		EnumerateAdapterOutput(adapterInfo);
		adapterInfos.push_back(adapterInfo);

		++index;
	}
}

bool Graphics::EnumerateAdapterOutput(const shared_ptr<D3DEnumAdapterInfo>& adapterInfo)
{
	ComPtr<IDXGIOutput> output;
	
	HRESULT hr = adapterInfo->adapter->EnumOutputs(0, &output);
	
	if (hr == DXGI_ERROR_NOT_FOUND)
		return false;

	auto outputInfo = make_shared<D3DEnumOutputInfo>();
	
	hr = output->GetDesc(&outputInfo->outputDesc);
	CHECK(hr);

	outputInfo->output = output;

	UINT numModes = 0;
	vector<DXGI_MODE_DESC> displayModes;
	DXGI_FORMAT format = DXGI_FORMAT_B8G8R8A8_UNORM;
	
	hr = output->GetDisplayModeList(format, DXGI_ENUM_MODES_INTERLACED, &numModes, nullptr);
	CHECK(hr);
	
	displayModes.assign(numModes, DXGI_MODE_DESC());
	hr = output->GetDisplayModeList(format, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModes.data());
	CHECK(hr);

	for (UINT i = 0; i < numModes; i++)
	{
		resolutionList.push_back(Vector2((float)displayModes[i].Width, (float)displayModes[i].Height));

		if (displayModes[i].Width == WIN_DEFAULT_WIDTH && displayModes[i].Height == WIN_DEFAULT_HEIGHT)
		{
			outputInfo->numerator = displayModes[i].RefreshRate.Numerator;
			outputInfo->denominator = displayModes[i].RefreshRate.Denominator;
		}
	}

	for (const Vector2& res : resolutionList)
		cout << res.x << " X " << res.y << '\n';

	adapterInfo->outputInfo = outputInfo;

	return true;
}

void Graphics::CreateSwapChain()
{
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));

	desc.BufferDesc.Width = 0;
	desc.BufferDesc.Height = 0;

	UINT maxVideoMemory = 0;
	for (UINT i = 0; i < adapterInfos.size(); i++)
	{
		if (adapterInfos[i]->adapterDesc.DedicatedVideoMemory > maxVideoMemory)
		{
			selectedAdapterIndex = i;
			maxVideoMemory = (UINT)adapterInfos[i]->adapterDesc.DedicatedVideoMemory;
		}
	}

	const auto& adapterInfo = adapterInfos[selectedAdapterIndex];

	if (bVsync)
	{
		desc.BufferDesc.RefreshRate.Numerator = adapterInfo->outputInfo->numerator;
		desc.BufferDesc.RefreshRate.Denominator = adapterInfo->outputInfo->denominator;
	}
	else
	{
		desc.BufferDesc.RefreshRate.Numerator = 0;
		desc.BufferDesc.RefreshRate.Denominator = 1;
	}

	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;

	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.BufferCount = 1;

	desc.OutputWindow = gHandle;
	desc.Windowed = true;
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	vector<D3D_FEATURE_LEVEL> featureLevel
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};

	D3D_FEATURE_LEVEL currentFeature;

	HRESULT hr = D3D11CreateDeviceAndSwapChain
	(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		featureLevel.data(),
		(UINT)featureLevel.size(),
		D3D11_SDK_VERSION,
		&desc,
		&swapChain,
		&device,
		&currentFeature,
		&deviceContext
	);
	CHECK(hr);

	numerator = adapterInfo->outputInfo->numerator;
	denominator = adapterInfo->outputInfo->denominator;

	gpuMemorySize = (UINT)adapterInfo->adapterDesc.DedicatedVideoMemory / 1024 / 1024;
	gpuDescription = adapterInfo->adapterDesc.Description;

	cout << "DedicatedVideoMemory : " << gpuMemorySize << '\n';
	wcout << "GPU Description : " << gpuDescription << '\n';

	cout << "Numerator : " << numerator << '\n';
	cout << "Denominator : " << denominator << '\n';
	cout << "RefreshRate : " << numerator / denominator << '\n';

	Resize(gWinWidth, gWinHeight);
}

void Graphics::CreateRenderTargetView()
{
	ComPtr<ID3D11Texture2D> backBuffer;

	HRESULT hr = swapChain->GetBuffer
	(
		0,
		__uuidof(ID3D11Texture2D),
		(void**)&backBuffer
	);
	CHECK(hr);

	hr = device->CreateRenderTargetView
	(
		backBuffer.Get(),
		nullptr,
		&rtv
	);
	CHECK(hr);
}

void Graphics::DeleteSuface()
{
	rtv.Reset();
}
