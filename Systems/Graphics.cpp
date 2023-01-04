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
	desc.BufferDesc.RefreshRate.Numerator = 60;		//����
	desc.BufferDesc.RefreshRate.Denominator = 1;	//�и�
	//60fps�� �ȴ�.
	//R8 G8 B8 A8(����)������ ǥ���Ѵ�.	
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//ȭ���� �׷��� �� �׷����� ����.(�ȼ��� �׷��� �� �׷����� ����.)
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	//���̰ų� �ø� �� ��� �� ���ΰ�.(������� �⺻ ����� ���󰣴�.)
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	
	//�������, �ȼ������� ȭ�鿡 ��µǱ� ������ �׸��� ���ó�� ���� �� �� �ִ�. 
	//SSAA MSAA ��Ƽ�ٸ���� ���� �� ���� ������ �ڿ������� ǥ���ϴ� ���̴�. 
	//SSAA x4 x16�� �ϳ��� �ȼ��� 4���� �ȼ��� ǥ���Ѵ�. 16���� �ȼ��� �ϳ��� �ȼ��� ǥ���Ѵ�.
	
	//���� �ø� ���ΰ�. �� ���� �ȼ��� ��� ǥ���� ���ΰ�. 4�� ������ SSAA x4 �ϳ��� �ȼ��� 4���� �ȼ��� ǥ���Ѵ�.
	desc.SampleDesc.Count = 1;	
	//0~1�� ���� ���� �� �ְ�, ������ �������� �����ϰ� ���ø��� �Ѵ�. ���귮�� �þ�� ������ �����ս��� ������ �� �ִ�.
	desc.SampleDesc.Quality = 0;
	//�׸� �� �ʿ��� ������ Render Target�̴�. Buffer�� �׸��� �ʿ��� �������� Ȱ���� ���̴�.
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.BufferCount = 1;
	//���� ����� �� ���ΰ�?
	desc.OutputWindow = gHandle;
	//��üȭ���̸� false, âȭ���̸� true. ��üȭ�鿡 ���� ������ ���� �ؾ��Ѵ�.
	desc.Windowed = true;
	//����ü���� �߻��� �� � ȿ���� �� ���ΰ�.
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;		//ȿ���� ���� �ʴ´�.
	//adapter �׷���ī���� ����.
	//Direct ������ ���� ���� ��� �´� ������ ã�� ���� featureLevel

	vector<D3D_FEATURE_LEVEL> featureLevel
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};
	D3D_FEATURE_LEVEL currentFeature;

	//���� ���� ���� ���ؼ� ������ �����.
	//HRESULT�� ��ȯ�ϴ� ������ ���� ������, ����� ������ �Ǿ����� Ȯ���ϱ� ���ؼ��̴�. 
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
	//�� ����������� ���, �����ߴٸ� ����.
	CHECK(hr);

	CreateBackBuffer();
}

void Graphics::CreateBackBuffer()
{	
	//���� ������ ���� �־��ִ� ���̴�. ���� �������� ���� �Ÿ� 0�� �־��ش�.
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
	//window���� Ű���� __, __uuidof()�������̽��� id�� �������� �Լ�
	//__uuidof(ID3D11Texture2D)���·� backBuffer�� �޾ƿ´�.
	hr = swapChain->GetBuffer
	(
		0,
		__uuidof(ID3D11Texture2D),
		(void**)&backBuffer
	);
	CHECK(hr);
	//�ؽ�ó�ڿ��� Ư¡. �ٷ� ����� �� ����. �ڿ��� ��� ������� view�� ������ �Ѵ�.
	//GetBuffer�� ���ؼ� ������� ���ҽ��� �������� ������ desc�� ���� ���� �ʾƵ� �ȴ�.
	//������ ���� �������� �ʰ� ���Ӱ� ����� �ʹٸ� ���� �Է��ؾ� �Ѵ�.
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
	//2D�� ���̰� �ǹ̰� ����.
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
}

void Graphics::Begin()
{
	//Input Asssembler(IA) >> Vertex Shader(VS) >> RS >> PS>> OM
	//������â�� ������ ������ ���ϰ�,
	deviceContext->RSSetViewports(1, &viewport);
	//�׸��� ���� ����� �ּҸ� �ְ�,
	deviceContext->OMSetRenderTargets(1, rtv.GetAddressOf(), nullptr);
	//������ �׷��� �͵��� �����.
	deviceContext->ClearRenderTargetView(rtv.Get(), clearColor);
}


void Graphics::End()
{
	HRESULT hr = swapChain->Present(1, 0);
	CHECK(hr);
}
