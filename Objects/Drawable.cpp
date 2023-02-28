#include "stdafx.h"
#include "Drawable.h"

Drawable::Drawable(const string& name, const Vector2& position, const Vector2& scale, const float& rotation, const wstring shaderPath)
	: Object(name), shaderPath(shaderPath)
{
	VB = make_unique<VertexBuffer>();

	VS = make_unique<VertexShader>();
	VS->Create(shaderPath, "VS");

	IB = make_unique<IndexBuffer>();

	IL = make_unique<InputLayout>();

	PS = make_unique<PixelShader>();
	PS->Create(shaderPath, "PS");

	AddComponent(make_shared<WorldComponent>(position, scale, rotation));
}

//Drawable& Drawable::operator=(const Drawable& other)
//{
//	// TODO: 여기에 return 문을 삽입합니다.
//}

void Drawable::Update()
{
	SUPER::Update();
}

void Drawable::Render()
{
	SUPER::Render();

	VB->SetIA();
	IB->SetIA();
	IL->SetIA();

	VS->SetShader();

	PS->SetShader();
}

void Drawable::SetShader(const wstring& shaderPath)
{
	this->shaderPath = shaderPath;
	VS->Clear();
	VS->Create(shaderPath, "VS");
	PS->Clear();
	PS->Create(shaderPath, "PS");
}

void Drawable::GUI()
{
	GetWorld()->GUI();
}

void Drawable::DrawCall(const D3D11_PRIMITIVE_TOPOLOGY& topology, const bool& indexed)
{
	DC->IASetPrimitiveTopology(topology);

	if (indexed)
		DC->DrawIndexed(IB->GetCount(), 0, 0);
	else
		DC->Draw(VB->GetCount(), 0);
}
