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
	//�ڿ��� �����Ѵ�. ���ҽ��� �����Ѵ�. ���̴��� ���ؼ� GPU���� ����� ���� �� �ִ�. GPU�� �ٷ�� ���� �Լ��� ������ ���̴��̴�.
	ID3D11Device* device = nullptr;
	//������ �ڿ��� ���̴����� �ѱ��.
	ID3D11DeviceContext* deviceContext = nullptr;
	IDXGISwapChain* swapChain = nullptr;
	ID3D11RenderTargetView* rtv = nullptr;
	D3D11_VIEWPORT viewport = { 0 };
	Color clearColor = { 0.4f, 0.4f, 0.4f, 1.0f };
};