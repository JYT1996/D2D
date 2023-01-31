#include "stdafx.h"
#include "Drawable.h"
//정점의 정보를 담을 수 있게 make_unique를 하지만, Create()를 사용하지는 않는다.
Drawable::Drawable(const string& name, const Vector2& position, const Vector2& scale, const float& rotation, const wstring shaderPath)
	: Object(name), shaderPath(shaderPath)
{
	vertexBuffer = make_unique<VertexBuffer>();

	vertexShader = make_unique<VertexShader>();
	vertexShader->Create(shaderPath, "VS");

	indexBuffer = make_unique<IndexBuffer>();

	inputLayout = make_unique<InputLayout>();

	pixelShader = make_unique<PixelShader>();
	pixelShader->Create(shaderPath, "PS");
	
	AddComponent(make_shared<WorldComponent>(position, scale, rotation));
}

//Drawable& Drawable::operator=(const Drawable& other)
//{
//	// TODO: 여기에 return 문을 삽입합니다.
//	return *this;
//}

void Drawable::Update()
{
	SUPER::Update();

	vertexBuffer->SetIA();
	indexBuffer->SetIA();
	inputLayout->SetIA();

	vertexShader->SetShader();

	pixelShader->SetShader();
}

void Drawable::Render()
{
	SUPER::Render();
}

void Drawable::DrawCall(const D3D11_PRIMITIVE_TOPOLOGY& topology, const bool& indexed)
{
	DC->IASetPrimitiveTopology(topology);
	
	if (indexed)
		DC->DrawIndexed(indexBuffer->GetCount(), 0, 0);
	else
		DC->Draw(vertexBuffer->GetCount(), 0);
}
