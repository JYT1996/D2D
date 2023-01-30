#include "stdafx.h"
#include "ColorRect.h"

ColorRect::ColorRect(const Vector2& position, const Vector2& scale, const float& rotation, Color color)
	: Drawable("ColorRect", position, scale, rotation, L"_Shaders/VertexColor.hlsl"), color(color)
{
	vertices.assign(4, VertexColor());
	vertices[0].position = Vector2(-0.5f, -0.5f);
	vertices[0].color = color;
	vertices[1].position = Vector2(-0.5f, 0.5f);
	vertices[1].color = color;
	vertices[2].position = Vector2(0.5f, -0.5f);
	vertices[2].color = color;
	vertices[3].position = Vector2(0.5f, 0.5f);
	vertices[3].color = color;

	indices = { 0, 1, 2, 2, 1, 3 };
	
	vertexBuffer->Create(vertices, D3D11_USAGE_DYNAMIC);
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
	DrawCall(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void ColorRect::SetColor(Color color)
{
	this->color = color;

	D3D11_MAPPED_SUBRESOURCE mappedSubResource;
	ZeroMemory(&mappedSubResource, sizeof(mappedSubResource));

	HRESULT hr = DC->Map(vertexBuffer->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedSubResource);
	CHECK(hr);
	{
		for (auto& vertex : vertices)
			vertex.color = color;

		memcpy(mappedSubResource.pData, vertices.data(), sizeof(vertices[0]) * vertices.size());
	}

	DC->Unmap(vertexBuffer->GetResource(), 0);
}
