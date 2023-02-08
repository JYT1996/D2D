#pragma once

struct D3DEnumAdapterInfo;
struct D3DEnumOutputInfo;

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

public:
	void Resize(const float& width, const float& height);
	void SetViewport(const float& width, const float& height);
	void SetViewport();
	void SetBackBufferToRTV();

private:
	void EnumerateAdapters();
	bool EnumerateAdapterOuput(const shared_ptr<D3DEnumAdapterInfo> &adapterInfo);

private:
	void CreateSwapChain();
	void CreateRenderTargetView();
	void DeleteSuface();

private:
	ComPtr<ID3D11Device> device = nullptr;
	ComPtr<ID3D11DeviceContext> deviceContext = nullptr;
	ComPtr<IDXGISwapChain> swapChain = nullptr;
	ComPtr<ID3D11RenderTargetView> rtv = nullptr;
	D3D11_VIEWPORT viewport = { 0 };
	Color clearColor = { 0.4f, 0.4f, 0.4f, 1.0f };

	UINT numerator = 0;
	UINT donominator = 1;

	UINT gpuMemorySize = 0;
	wstring gpuDescription = L"";
	//수직동기화
	bool bVsync = true;

	vector<shared_ptr<D3DEnumAdapterInfo>> adapterInfos;
	UINT selectedAdapterIndex = 0;

	vector<Vector2> resolutionList;
};

struct D3DEnumAdapterInfo
{
	UINT adapterOrdinal = 0;
	ComPtr<IDXGIAdapter1> adapter;
	DXGI_ADAPTER_DESC1 adapterDesc = { 0 };

	shared_ptr<D3DEnumOutputInfo> outputInfo;
};

struct D3DEnumOutputInfo
{
	ComPtr<IDXGIOutput> output;
	DXGI_OUTPUT_DESC outputDesc = { 0 };

	UINT numerator = 0;
	UINT denominator = 1;
};