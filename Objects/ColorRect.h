#pragma once

class ColorRect
{
public:
	ColorRect() = default;
	ColorRect(Vector3 scale, float rotation, Vector3 translation);
	~ColorRect() {};

public:
	//getter, setter
	Matrix GetWorld() { return world; }
	UINT GetIndicseSize() { return (UINT)indices.size(); }
	void SetColorRect();
	void Move(Vector3 translation);

//MOVE, Rotate, Scale 함수 구현.

private:
	//포지션 스케일 로테이션
	Matrix world;
	Vector3 scale;
	float rotation;
	Vector3 translation;

	vector<VertexColor> vertices;
	VertexBuffer vertexBuffer;
	VertexShader vertexShader;

	vector<UINT> indices;
	IndexBuffer indexBuffer;

	InputLayout inputLayout;

	PixelShader pixelShader;	
};
