#include "stdafx.h"
#include "Circle.h"

Circle::Circle(const Vector2& position, const Vector2& scale, const float& rotation, Color color)
	: Drawable("Circle", position, scale, rotation, L"_Shaders/VertexColor.hlsl"), color(color)
{
	vertices.assign(40, VertexColor());
	for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i].position = Vector2(0.5f * cosf(XMConvertToRadians(360.0f - (360.0f / vertices.size()) * i )), 0.5f * sinf(XMConvertToRadians(360.0f - (360.0f / vertices.size()) * i)));
		vertices[i].color = color;
		indices.emplace_back(i);
	}
		indices.emplace_back(0);

	vertexBuffer->Create(vertices, D3D11_USAGE_DYNAMIC);
	indexBuffer->Create(indices, D3D11_USAGE_IMMUTABLE);
	inputLayout->Create(VertexColor::descs, VertexColor::count, vertexShader->GetBlob());
}

void Circle::Update()
{
	SUPER::Updata();
}

void Circle::Render()
{
	SUPER::Render();
	DrawCall(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
}

void Circle::SetColor(Color color)
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
