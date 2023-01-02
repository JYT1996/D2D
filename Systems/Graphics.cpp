#include "stdafx.h"
#include "Graphics.h"

Graphics::Graphics()
{
	Init();
}

Graphics::~Graphics()
{
	//����ڰ� �����Ҵ��� �ϰ� �����ϴ� ���� �ƴϱ� ������ Release()�� ���ؼ� ���������� �ؾ��Ѵ�.
	//������ �ص� nullptr�� ���� �ʱ� ������ nullptr�� ���� ��ũ�θ� �������.
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
	desc.BufferDesc.RefreshRate.Numerator = 60;		//����
	desc.BufferDesc.RefreshRate.Denominator = 1;	//�и�
	//60fps�� �ȴ�.
	//R8 G8 B8 A8������ ǥ���Ѵ�.	
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
