#include "stdafx.h"
#include "FilledCircle.h"

FilledCircle::FilledCircle(const Vector2& position, const Vector2& scale, const float& rotation, Color color)
	: Drawable("FilledCircle", position, scale, rotation, L"_Shaders/VertexColor.hlsl"), color(color)
{
	vertices.assign(20, VertexColor());
	vertices[vertices.size() - 1].position = Vector2(0.0f, 0.0f);
	vertices[vertices.size() - 1].color = color;

	for (int i = 0; i < vertices.size() - 1; i++)
	{
		vertices[i].position = Vector2(0.5f * cosf(XMConvertToRadians(360.0f - (360.0f / (vertices.size() - 1)) * i)), 0.5f * sinf(XMConvertToRadians(360.0f - (360.0f / (vertices.size() - 1)) * i)));
		vertices[i].color = color;
	}

	for (int i = 0, j = 1; i < vertices.size() - 1; i++, j++)
	{
		if (i == vertices.size() - 2)
			j = 0;
		indices.emplace_back(i);
		indices.emplace_back(j);
		indices.emplace_back(vertices.size() - 1);
	}

	vertexBuffer->Create(vertices, D3D11_USAGE_DYNAMIC);
	indexBuffer->Create(indices, D3D11_USAGE_IMMUTABLE);
	inputLayout->Create(VertexColor::descs, VertexColor::count, vertexShader->GetBlob());
}

void FilledCircle::Update()
{
	SUPER::Updata();
}

void FilledCircle::Render()
{
	SUPER::Render();
	DrawCall(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void FilledCircle::SetColor(Color color)
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
