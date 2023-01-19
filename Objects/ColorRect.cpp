#include "stdafx.h"
#include "ColorRect.h"

ColorRect::ColorRect(const string& name, const Vector2& position, const Vector2& scale, const float& rotation, const wstring shaderPath)
	: Drawable(name, position, scale, rotation, shaderPath)
{
	vertices.assign(4, VertexColor());
	vertices[0].position = Vector2(-0.5f, -0.5f);
	vertices[0].color = RED;
	vertices[1].position = Vector2(-0.5f, 0.5f);
	vertices[1].color = RED;
	vertices[2].position = Vector2(0.5f, -0.5f);
	vertices[2].color = RED;
	vertices[3].position = Vector2(0.5f, 0.5f);
	vertices[3].color = RED;

	indices = { 0, 1, 2, 2, 1, 3 };

	vertexBuffer->Create(vertices, D3D11_USAGE_IMMUTABLE);
	indexBuffer->Create(indices, D3D11_USAGE_IMMUTABLE);	
	inputLayout->Create(VertexColor::descs, VertexColor::count, vertexShader->GetBlob());
}

void ColorRect::Update()
{
	SUPER::Updata();
}

void ColorRect::Render()
{		
	SUPER::Render();
	DrawCall(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, true);
}
