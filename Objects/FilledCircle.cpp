#include "stdafx.h"
#include "FilledCircle.h"

FilledCircle::FilledCircle(const Vector2& position, const Vector2& scale, const float& rotation, const Color& color)
	: Drawable("FilledCircle", position, scale, rotation, L"_Shaders/Vertex.hlsl")
{
	vertices.assign(20, Vertex());
	vertices[vertices.size() - 1].position = Vector2(0.0f, 0.0f);

	for (int i = 0; i < vertices.size() - 1; i++)
	{
		vertices[i].position = Vector2(0.5f * cosf(XMConvertToRadians(360.0f - (360.0f / (vertices.size() - 1)) * i)), 0.5f * sinf(XMConvertToRadians(360.0f - (360.0f / (vertices.size() - 1)) * i)));
	}

	for (int i = 0, j = 1; i < vertices.size() - 1; i++, j++)
	{
		if (i == vertices.size() - 2)
			j = 0;
		indices.emplace_back(i);
		indices.emplace_back(j);
		indices.emplace_back(vertices.size() - 1);
	}

	vertexBuffer->Create(vertices, D3D11_USAGE_IMMUTABLE);
	indexBuffer->Create(indices, D3D11_USAGE_IMMUTABLE);
	inputLayout->Create(Vertex::descs, Vertex::count, vertexShader->GetBlob());
	
	AddComponent(make_shared<ColorComponent>(color, 0));
}

void FilledCircle::Update()
{
	SUPER::Update();
}

void FilledCircle::Render()
{
	SUPER::Render();
	DrawCall(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

