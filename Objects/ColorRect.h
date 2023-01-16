#pragma once

class ColorRect
{
public:
	ColorRect(Vector3 scale, float rotation, Vector3 translation);
	~ColorRect() {};

public:
	//getter, setter
	ColorRect* GetColorRect();
	void SetColorRect();
	void Move(Vector3 translation);
	void Rotate(float rotation);
	void Scale(Vector3 scale);

		//MOVE, Rotate, Scale �Լ� ����.

private:
	//������ ������ �����̼�
	Matrix world;
	Vector3 scale;
	float rotation; 
	Vector3 translation;

	vector<VertexColor> vertices;
	VertexBuffer vertexBuffer;

	vector<UINT> indices;
	IndexBuffer indexBuffer;

	ComPtr<ID3DBlob> vsBlob;
	VertexShader vertexShader;

	InputLayout inputLayout;

	ComPtr<ID3DBlob> psBlob;
	PixelShader pixelShader;

	ComPtr<ID3D11Buffer> gpuBuffer;
};
