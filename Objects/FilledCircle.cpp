#include "stdafx.h"
#include "FilledCircle.h"

FilledCircle::FilledCircle(const Vector2& position, const Vector2& scale, const float& rotation, const size_t& segments, const Color& color)
	: Drawable("FilledCircle", position, scale, rotation, L"_Shaders/Vertex.hlsl"), segments(segments)
{
	vertices.assign(segments + 1, Vertex());
	vertices[0].position = Vector2();

	for (size_t i = 1; i <= segments; i++)
	{
		float theta = 2 * XM_PI * i / segments;

		vertices[i].position = Vector2(cosf(theta), -sinf(theta)) / 2.0f;
	}

	indices.assign(segments * 3, sizeof(UINT));

	for (size_t i = 0; i < segments; i++)
	{
		indices[i * 3] = 0;
		indices[i * 3 + 1] = (UINT)i + 1;
		if(i == segments - 1)
			indices[i * 3 + 2] = 1;
		else
			indices[i * 3 + 2] = (UINT)i + 2;
	}

	vertexBuffer->Create(vertices, D3D11_USAGE_IMMUTABLE);
	indexBuffer->Create(indices, D3D11_USAGE_IMMUTABLE);
	inputLayout->Create(Vertex::descs, Vertex::count, vertexShader->GetBlob());
	
	AddComponent(make_shared<ColorComponent>(color, 0));
	AddComponent(make_shared<ColliderComponent>(ColliderType::CIRCLE));
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