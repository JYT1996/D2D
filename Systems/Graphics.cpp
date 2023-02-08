#include "stdafx.h"
#include "Graphics.h"

Graphics::Graphics()
{
	Init();
}

Graphics::~Graphics()
{	
}

void Graphics::Init()
{
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));

	desc.BufferDesc.Width = 0;
	desc.BufferDesc.Height = 0;
	desc.BufferDesc.RefreshRate.Numerator = 60;	
	desc.BufferDesc.RefreshRate.Denominator = 1;
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
	CreateBackBuffer();
}

void Graphics::CreateBackBuffer()
{	
	HRESULT hr = swapChain->ResizeBuffers
	(
		0,
		(UINT)gWinWidth,
		(UINT)gWinHeight,
		DXGI_FORMAT_UNKNOWN,
		0
	);
	CHECK(hr);

	ComPtr<ID3D11Texture2D> backBuffer = nullptr;

	hr = swapChain->GetBuffer
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

	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	viewport.Width = gWinWidth;
	viewport.Height = gWinHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
}

void Graphics::Begin()
{
	deviceContext->RSSetViewports(1, &viewport);
	deviceContext->OMSetRenderTargets(1, rtv.GetAddressOf(), nullptr);
	deviceContext->ClearRenderTargetView(rtv.Get(), clearColor);
}


void Graphics::End()
{
	HRESULT hr = swapChain->Present(1, 0);
	CHECK(hr);
}

void Graphics::Resize(const float& width, const float& height)
{
}

void Graphics::SetViewport(const float& width, const float& height)
{
}

void Graphics::SetViewport()
{
}

void Graphics::SetBackBufferToRTV()
{
}
//adapter를 열거한다.
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

		EnumerateAdapterOuput(adapterInfo);
		adapterInfos.push_back(adapterInfo);

		++index;
	}
}
//Adapter의 연결된 것을 열거한다
bool Graphics::EnumerateAdapterOuput(const shared_ptr<D3DEnumAdapterInfo> &adapterInfo)
{
	ComPtr<IDXGIOutput> output;
	//sturct 안에 있는 adapterInfo의 adapter에 연결된 디스플레이를 받아 왔다.
	HRESULT hr = adapterInfo->adapter->EnumOutputs(0, &output);
	//번호에 맞는 output을 찾지 못했다는 뜻이다.
	if (hr == DXGI_ERROR_NOT_FOUND)
		return false;

	auto outputInfo = make_shared<D3DEnumOutputInfo>();
	//위에서 연결한 DESC를 outputInfo에 넣어준다.
	hr = output->GetDesc(&outputInfo->outputDesc);
	CHECK(hr);

	outputInfo->output = output;

	UINT numModes = 0;
	vector<DXGI_MODE_DESC> displayModes;
	DXGI_FORMAT format = DXGI_FORMAT_B8G8R8A8_UNORM;
	//디스플레이에서 지원하는 해상도가 다를 수 있다. 60 Hz 100 Hz같이 모드가 나뉠 수 있다.
	//INTERLACED 모니터의 출력 방식
	//모니터마다 모드의 갯수가 다르기 때문에 numModes에 모드가 몇개 있는지 받아온다.
	hr = output->GetDisplayModeList(format, DXGI_ENUM_MODES_INTERLACED, &numModes, nullptr);
	CHECK(hr);
	//그리고 모드갯수만큼 vector의 공간을 확보하고 vector에 값을 넣는다.
	displayModes.assign(numModes, DXGI_MODE_DESC());
	hr = output->GetDisplayModeList(format, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModes.data());
	CHECK(hr);

	for (UINT i = 0; i < numModes; i++)
	{
		//현재 연결된 해상도 리스트를 받을 수 있다.
		resolutionList.push_back(Vector2((float)displayModes[i].Width, (float)displayModes[i].Height));

		if (displayModes[i].Width == WIN_DEFAULT_WIDTH && displayModes[i].Height == WIN_DEFAULT_HEIGHT)
		{
			//보통 마지막에 최대 주사율이 위치한다.
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
	device.Reset();
	deviceContext.Reset();
	swapChain.Reset();

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

	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
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
}

void Graphics::CreateRenderTargetView()
{
}

void Graphics::DeleteSuface()
{
}
