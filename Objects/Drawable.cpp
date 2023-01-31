#include "stdafx.h"
#include "Drawable.h"
//������ ������ ���� �� �ְ� make_unique�� ������, Create()�� ��������� �ʴ´�.
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
//	// TODO: ���⿡ return ���� �����մϴ�.
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
