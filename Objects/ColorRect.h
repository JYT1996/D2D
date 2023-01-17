#pragma once

class ColorRect
{
public:
	ColorRect();
	~ColorRect() {};

public:
	void SetWorldBuffer();
	void SetCPUBuffer();
	void Render();

	void Move(float x, float y, float z);
	void Rotate();
	void Scale();

	void SetScale(float x, float y, float z)
	{
		_scale = XMMatrixScaling(x, y, z);
	};

	void SetRotation(float Degrees)
	{
		_rotation = XMMatrixRotationZ(XMConvertToRadians(Degrees));
	};

	void SetTranslation(float x, float y, float z)
	{
		_translation = XMMatrixTranslation(_translation._31 + x, _translation._32 + y, _translation._33 + z);
	};

//MOVE, Rotate, Scale 함수 구현.
private:
	//포지션 스케일 로테이션
	vector<VertexColor> vertices;
	VertexBuffer vertexBuffer;

	vector<UINT> indices;
	IndexBuffer indexBuffer;

	VertexShader vertexShader;

	InputLayout inputLayout;
	
	PixelShader pixelShader;

	unique_ptr<WorldBuffer> cpuBuffer;
	Matrix world;
	Matrix _scale, _rotation, _translation;

	ComPtr<ID3D11RasterizerState> RS;
};
