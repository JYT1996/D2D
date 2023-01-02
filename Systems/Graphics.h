#pragma once

class Graphics
{
	DECLARE_SINGLETON(Graphics);

public:
	void Init();
	void VreateBackBuffer();

	ID3D11Device* GetDevice() { return device; }
	ID3D11DeviceContext* GetDC() {return deviceContext; }

	void Begin();
	void End();

private:
	//자원을 생성한다. 리소스를 생성한다. 쉐이더를 통해서 GPU에게 명령을 내릴 수 있다. GPU를 다루기 위한 함수의 집합이 쉐이더이다.
	ID3D11Device* device = nullptr;
	//생성된 자원을 쉐이더에게 넘긴다.
	ID3D11DeviceContext* deviceContext = nullptr;
	IDXGISwapChain* swapChain = nullptr;
	ID3D11RenderTargetView* rtv = nullptr;
	D3D11_VIEWPORT viewport = { 0 };
	Color clearColor = { 0.4f, 0.4f, 0.4f, 1.0f };
};