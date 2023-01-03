#pragma once

class Graphics
{
	DECLARE_SINGLETON(Graphics);

public:
	void Init();
	void CreateBackBuffer();
	
	ComPtr<ID3D11Device> GetDevice() const { return device; }
	ComPtr<ID3D11DeviceContext> GetDC() const {return deviceContext; }

	void Begin();
	void End();

private:
	//스마트포인터로 사용하기 위해 WRL.h를 포함한다. COM Pointer라고 한다.
	//객체의 사용이 끝나면 알아서 동적해제를 해준다.
	ComPtr<ID3D11Device> device = nullptr;
	ComPtr<ID3D11DeviceContext> deviceContext = nullptr;
	ComPtr<IDXGISwapChain> swapChain = nullptr;
	ComPtr<ID3D11RenderTargetView> rtv = nullptr;
	//윈도우창을 생성했을 시 보여지는 영역.
	D3D11_VIEWPORT viewport = { 0 };
	Color clearColor = { 0.4f, 0.4f, 0.4f, 1.0f };
};