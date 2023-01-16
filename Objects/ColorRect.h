#pragma once

class ColorRect
{
public:
	ColorRect() = default;
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

	VertexColor vertexColor;

	vector<VertexColor> vertices;
	VertexBuffer vertexBuffer;

	VertexShader vertexShader;

	vector<UINT> indices;
	IndexBuffer indexBuffer;

	InputLayout inputLayout;

	PixelShader pixelShader;

	ComPtr<ID3D11Buffer> gpuBuffer;
};
