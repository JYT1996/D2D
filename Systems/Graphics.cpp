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
	desc.BufferDesc.RefreshRate.Numerator = 60;		//분자
	desc.BufferDesc.RefreshRate.Denominator = 1;	//분모
	//60fps가 된다.
	//R8 G8 B8 A8(투명도)비율로 표현한다.	
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//화면이 그려질 때 그려지는 순서.(픽셀이 그려질 때 그려지는 순서.)
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	//줄이거나 늘릴 때 어떻게 할 것인가.(모니터의 기본 사양을 따라간다.)
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	
	//계단현상, 픽셀단위로 화면에 출력되기 때문에 그림이 계단처럼 각이 질 수 있다. 
	//SSAA MSAA 안티앨리어싱 각이 진 것을 뭉개서 자연스럽게 표현하는 것이다. 
	//SSAA x4 x16은 하나의 픽셀을 4개의 픽셀로 표현한다. 16개의 픽셀로 하나의 픽셀을 표현한다.
	
	//몇배로 늘린 것인가. 한 개의 픽셀을 몇개로 표현할 것인가. 4를 넣으면 SSAA x4 하나의 픽셀을 4개의 픽셀로 표현한다.
	desc.SampleDesc.Count = 1;	
	//0~1의 값을 넣을 수 있고, 높으면 높을수록 정교하게 샘플링을 한다. 연산량이 늘어나기 때문에 퍼포먼스가 떨어질 수 있다.
	desc.SampleDesc.Quality = 0;
	//그릴 때 필요한 공간이 Render Target이다. Buffer를 그림에 필요한 공간으로 활용할 것이다.
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.BufferCount = 1;
	//어디로 출력을 할 것인가?
	desc.OutputWindow = gHandle;
	//전체화면이면 false, 창화면이면 true. 전체화면에 대한 설정을 따로 해야한다.
	desc.Windowed = true;
	//스왑체인이 발생할 때 어떤 효과를 줄 것인가.
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;		//효과를 주지 않는다.
	//adapter 그래픽카드의 정보.
	//Direct 버전이 맞지 않을 경우 맞는 버전을 찾기 위한 featureLevel

	vector<D3D_FEATURE_LEVEL> featureLevel
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};
	D3D_FEATURE_LEVEL currentFeature;

	//위에 넣은 값을 통해서 실제로 만든다.
	//HRESULT로 반환하는 이유는 값이 들어갔지만, 제대로 생성이 되었는지 확인하기 위해서이다. 
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
	//잘 만들어졌으면 양수, 실패했다면 음수.
	CHECK(hr);

	CreateBackBuffer();
}

void Graphics::CreateBackBuffer()
{	
	//값을 변경할 값만 넣어주는 것이다. 값을 변경하지 않을 거면 0을 넣어준다.
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
	//window전용 키워드 __, __uuidof()인터페이스의 id를 가져오는 함수
	//__uuidof(ID3D11Texture2D)형태로 backBuffer를 받아온다.
	hr = swapChain->GetBuffer
	(
		0,
		__uuidof(ID3D11Texture2D),
		(void**)&backBuffer
	);
	CHECK(hr);
	//텍스처자원의 특징. 바로 사용할 수 없다. 자원을 어떻게 사용할지 view를 만들어야 한다.
	//GetBuffer를 통해서 만들어진 리소스를 가져오기 때문에 desc에 값을 넣지 않아도 된다.
	//하지만 값을 가져오지 않고 새롭게 만들고 싶다면 값을 입력해야 한다.
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
	//2D라서 깊이가 의미가 없다.
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
}

void Graphics::Begin()
{
	//Input Asssembler(IA) >> Vertex Shader(VS) >> RS >> PS>> OM
	//윈도우창에 보여질 영역을 정하고,
	deviceContext->RSSetViewports(1, &viewport);
	//그리기 위한 장소의 주소를 주고,
	deviceContext->OMSetRenderTargets(1, rtv.GetAddressOf(), nullptr);
	//이전에 그려진 것들을 지운다.
	deviceContext->ClearRenderTargetView(rtv.Get(), clearColor);
}


void Graphics::End()
{
	HRESULT hr = swapChain->Present(1, 0);
	CHECK(hr);
}
