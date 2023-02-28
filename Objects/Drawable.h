#pragma once

class Drawable : public Object
{
public:
	Drawable(const string& name, const Vector2& position, const Vector2& scale, const float& rotation, const wstring shaderPath = L"");
	Drawable(const Drawable& other) : Drawable(other.name, other.GetWorld()->GetPosition(), other.GetWorld()->GetScale(), other.GetWorld()->GetRotation(), other.shaderPath) {}

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
	unique_ptr<VertexBuffer> vertexBuffer;
	unique_ptr<VertexShader> vertexShader;
	unique_ptr<IndexBuffer> indexBuffer;
	unique_ptr<InputLayout> inputLayout;

	unique_ptr<PixelShader> pixelShader;

protected:
	wstring shaderPath = L"";
};
