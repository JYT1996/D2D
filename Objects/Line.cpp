#include "stdafx.h"
#include "Line.h"

Line::Line(const Vector2& position, const Vector2& scale, const float& rotation, Color color)
	: Drawable("Line", position, scale, rotation, L"_Shaders/VertexColor.hlsl"), color(color)
{
	vertices.assign(2, VertexColor());
	vertices[0].position = Vector2(-0.5f, -0.5f);
	vertices[0].color = color;
	vertices[1].position = Vector2(-0.5f, 0.5f);
	vertices[1].color = color;

	indices = { 0, 1 };

	vertexBuffer->Create(vertices, D3D11_USAGE_IMMUTABLE);
	indexBuffer->Create(indices, D3D11_USAGE_IMMUTABLE);
	inputLayout->Create(VertexColor::descs, VertexColor::count, vertexShader->GetBlob());
}

void Line::Update()
{
	SUPER::Updata();
}

void Line::Render()
{
	SUPER::Render();
	DrawCall(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
}

void Line::SetColor(Color color)
{
	/*this->color = color;

	D3D11_MAPPED_SUBRESOURCE mappedSubResource;
	ZeroMemory(&mappedSubResource, sizeof(mappedSubResource));

	DC->Map(vertexBuffer->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubResource);
	{
		for (auto& vertex : vertices)
			vertex.color = color;

		memcpy(mappedSubResource.pData, vertices.data(), sizeof(vertices[0]) * vertices.size());
	}

	DC->Unmap(vertexBuffer->GetResource(), 0);*/
}
