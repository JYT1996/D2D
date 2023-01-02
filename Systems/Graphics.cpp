#include "stdafx.h"
#include "Graphics.h"

Graphics::Graphics()
{
	Init();
}

Graphics::~Graphics()
{
	//사용자가 동적할당을 하고 해제하는 것이 아니기 때문에 Release()를 통해서 동적해제를 해야한다.
	//해제를 해도 nullptr을 하지 않기 때문에 nullptr을 해줄 메크로를 만들었다.
	SAFE_RELEASE(rtv);
	SAFE_RELEASE(swapChain);
	SAFE_RELEASE(deviceContext);
	SAFE_RELEASE(device);
}

void Graphics::Init()
{
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));

	DXGI_MODE_DESC BufferDesc;
	DXGI_SAMPLE_DESC SampleDesc;
	DXGI_USAGE BufferUsage;
	UINT BufferCount;
	HWND OutputWindow;
	BOOL Windowed;
	DXGI_SWAP_EFFECT SwapEffect;
	UINT Flags;

	UINT Width;
	UINT Height;
	DXGI_RATIONAL RefreshRate;
	DXGI_FORMAT Format;
	DXGI_MODE_SCANLINE_ORDER ScanlineOrdering;
	DXGI_MODE_SCALING Scaling;

	desc.BufferDesc.Width = 0;
	desc.BufferDesc.Height = 0;
	desc.BufferDesc.RefreshRate.Numerator = 60;		//분자
	desc.BufferDesc.RefreshRate.Denominator = 1;	//분모
	//60fps가 된다.
	//R8 G8 B8 A8비율로 표현한다.	
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

}

void Graphics::VreateBackBuffer()
{
}

void Graphics::Begin()
{
}

void Graphics::End()
{
}
