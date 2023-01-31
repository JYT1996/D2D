#include "stdafx.h"
#include "ColorRect.h"

ColorRect::ColorRect(const Vector2& position, const Vector2& scale, const float& rotation, const Color& color)
	: Drawable("ColorRect", position, scale, rotation, L"_Shaders/Vertex.hlsl")
{
	//VertexColor가 아닌 Vertex이기 때문에 Color값은 없어도 된다.
	vertices.assign(4, Vertex());
	vertices[0].position = Vector2(-0.5f, -0.5f);
	vertices[1].position = Vector2(-0.5f, 0.5f);
	vertices[2].position = Vector2(0.5f, -0.5f);
	vertices[3].position = Vector2(0.5f, 0.5f);

	indices = { 0, 1, 2, 2, 1, 3 };
	
	vertexBuffer->Create(vertices, D3D11_USAGE_IMMUTABLE);
	indexBuffer->Create(indices, D3D11_USAGE_IMMUTABLE);
	inputLayout->Create(Vertex::descs, Vertex::count, vertexShader->GetBlob());
	//Color를 담당할 Component를 추가한다. ColorComponent는 생성할 때 색상과 슬릇의 번호를 필요로 한다.
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
