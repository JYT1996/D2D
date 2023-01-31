#pragma once
//�׸��� ���� ����� ���� Object
class Drawable : public Object
{
public:
	Drawable(const string& name, const Vector2& position, const Vector2& scale, const float& rotation, const wstring shaderPath);
	//���� ��������ڸ� ����ϸ� �������� �ּҵ� �������� ������ ��� ����.
	//Drawable(const Drawable& other) : Object(other) { *this = other; }
	//Drawable& operator=(const Drawable& other);

	shared_ptr<WorldComponent> GetWorld() const { return GetComponent<WorldComponent>("World"); }

public:
	void Update() override;
	void Render() override;

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
