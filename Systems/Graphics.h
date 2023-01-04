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
	//����Ʈ�����ͷ� ����ϱ� ���� WRL.h�� �����Ѵ�. COM Pointer��� �Ѵ�.
	//��ü�� ����� ������ �˾Ƽ� ���������� ���ش�.
	ComPtr<ID3D11Device> device = nullptr;
	ComPtr<ID3D11DeviceContext> deviceContext = nullptr;
	ComPtr<IDXGISwapChain> swapChain = nullptr;
	ComPtr<ID3D11RenderTargetView> rtv = nullptr;
	//������â�� �������� �� �������� ����.
	D3D11_VIEWPORT viewport = { 0 };
	Color clearColor = { 0.4f, 0.4f, 0.4f, 1.0f };
};