#include "stdafx.h"
#include "ColorRect.h"

ColorRect::ColorRect(const Vector2& position, const Vector2& scale, const float& rotation, const Color& color)
	: Drawable("ColorRect", position, scale, rotation, L"_Shaders/Vertex.hlsl")
{
	//VertexColor�� �ƴ� Vertex�̱� ������ Color���� ��� �ȴ�.
	vertices.assign(4, Vertex());
	vertices[0].position = Vector2(-0.5f, -0.5f);
	vertices[1].position = Vector2(-0.5f, 0.5f);
	vertices[2].position = Vector2(0.5f, -0.5f);
	vertices[3].position = Vector2(0.5f, 0.5f);

	indices = { 0, 1, 2, 2, 1, 3 };
	
	vertexBuffer->Create(vertices, D3D11_USAGE_IMMUTABLE);
	indexBuffer->Create(indices, D3D11_USAGE_IMMUTABLE);
	inputLayout->Create(Vertex::descs, Vertex::count, vertexShader->GetBlob());
	//Color�� ����� Component�� �߰��Ѵ�. ColorComponent�� ������ �� ����� ������ ��ȣ�� �ʿ�� �Ѵ�.
	AddComponent(make_shared<ColorComponent>(color, 0));
}

void ColorRect::Update()
{
	SUPER::Update();
}

void ColorRect::Render()
{		
	SUPER::Render();
	DrawCall(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
