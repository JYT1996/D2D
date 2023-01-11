#pragma once

struct VertexColor
{
	Vector2 position;
	Color color;
};

struct VertexTexture
{
	Vector2 position;
	Vector2 uv;
};

struct TransformData
{
	Matrix world;
	Matrix view;
	Matrix projection;	
};

class Program
{
public:
	Program();
	~Program();

public:
	void Update();
	void Render();

private:
	//vector<VertexColor> vertices;
	vector<VertexTexture> vertices;
	ComPtr<ID3D11Buffer> vertexBuffer;

	vector<UINT> indices;
	ComPtr<ID3D11Buffer> indexBuffer;

	ComPtr<ID3DBlob> vsBlob;
	ComPtr<ID3D11VertexShader> vertexShader;

	ComPtr<ID3D11InputLayout> inputLayout;

	ComPtr<ID3DBlob> psBlob;
	ComPtr<ID3D11PixelShader> pixelShader;

	Matrix world, view, projection;
	
	TransformData cpuBuffer;
	ComPtr<ID3D11Buffer> gpuBuffer;

	ComPtr<ID3D11RasterizerState> RS;

	ComPtr<ID3D11ShaderResourceView> SRV;
	ComPtr<ID3D11SamplerState> samplerState;
	ComPtr<ID3D11BlendState> blendState;
};