#include "stdafx.h"
#include "Circle.h"

Circle::Circle(const Vector2& position, const Vector2& scale, const float& rotation, const size_t& segments, const Color& color)
	: Drawable("Circle", position, scale, rotation, L"_Shaders/Vertex.hlsl"), segments(segments)
{
	vertices.assign(segments + 1, Vertex());

	for (size_t i = 0; i <= segments; ++i)
	{
		float theta = 2 * XM_PI * i / segments;

		vertices[i].position = Vector2(cosf(theta), -sinf(theta)) / 2.0f;
	}

	vertexBuffer->Create(vertices, D3D11_USAGE_IMMUTABLE);

	inputLayout->Create(Vertex::descs, Vertex::count, vertexShader->GetBlob());

	AddComponent(make_shared<ColorComponent>(color, 0));
	AddComponent(make_shared<ColliderComponent>(ColliderType::CIRCLE));
}

void Circle::Update()
{
	SUPER::Update();
}

void Circle::Render()
{
	SUPER::Render();

	DrawCall(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP, false);
}
