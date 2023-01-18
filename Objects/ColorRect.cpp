#include "stdafx.h"
#include "ColorRect.h"

ColorRect::ColorRect(const Vector2& position, const Vector2& scale, const float& rotation)
	: position(position), scale(scale), rotation(XMConvertToRadians(rotation))
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
	
	vertexBuffer = make_unique<VertexBuffer>();
	vertexBuffer->Create(vertices, D3D11_USAGE_IMMUTABLE);
	
	vertexShader = make_unique<VertexShader>();
	vertexShader->Create(L"_Shaders/VertexColor.hlsl", "VS");

	indexBuffer = make_unique<IndexBuffer>();
	indexBuffer->Create(indices,D3D11_USAGE_IMMUTABLE);
	
	inputLayout = make_unique<InputLayout>();
	inputLayout->Create(VertexColor::descs, VertexColor::count, vertexShader->GetBlob());

	pixelShader = make_unique<PixelShader>();
	pixelShader->Create(L"_Shaders/VertexColor.hlsl", "PS");

	worldBuffer = make_unique<WorldBuffer>();			
}

void ColorRect::Update()
{
	S = XMMatrixScalingFromVector(scale);
	R = XMMatrixRotationZ(-rotation);
	T = XMMatrixTranslationFromVector(position);
	
	world = S * R * T;	

	worldBuffer->SetWorld(world);
}

void ColorRect::Render()
{	
	vertexBuffer->SetIA();
	indexBuffer->SetIA();
	inputLayout->SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	worldBuffer->SetVSBuffer(0);

	vertexShader->SetShader();
	pixelShader->SetShader();

	DC->DrawIndexed(indexBuffer->GetCount(), 0, 0);
}
