#pragma once

class Drawable : public Object
{
public:
	Drawable(const string& name, const Vector2& position, const Vector2& scale, const float& rotation, const wstring shaderPath = L"");
	Drawable(const Drawable& other) : Drawable(other.name, other.GetWorld()->GetPosition(), other.GetWorld()->GetScale(), other.GetWorld()->GetRotation(), other.shaderPath) { }

public:
	void Update() override;
	void Render() override;

public:
	void SetShader(const wstring& shaderPath);

public:
	void GUI();

public:
	void DrawCall(const D3D11_PRIMITIVE_TOPOLOGY& topology, const bool& indexed = true);

protected:
	unique_ptr<VertexBuffer> VB;
	unique_ptr<VertexShader> VS;
	unique_ptr<IndexBuffer> IB;
	unique_ptr<InputLayout> IL;

	unique_ptr<PixelShader> PS;

protected:
	wstring shaderPath = L"";
};