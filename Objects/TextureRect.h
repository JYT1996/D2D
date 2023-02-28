#pragma once

class TextureRect : public Drawable
{
public:
	TextureRect(const Vector2& position, const Vector2& scale, const float& rotation, const wstring& texturePath = L"");
	TextureRect(const TextureRect& other) : TextureRect(other.GetWorld()->GetPosition(), other.GetWorld()->GetScale(), other.GetWorld()->GetRotation(), other.GetTexture()->GetPath()) {}

public:
	void Update() override;
	void Render() override;

public:
	void GUI(int ordinal);
	
public:
	shared_ptr<TextureComponent> GetTexture() const { return GetComponent<TextureComponent>("Texture"); }

private:
	void ChangeImageFunc(const wstring& path = L"");
	void ChangeShaderFunc(const wstring& path = L"");
	void SaveTextAsFile(const string& text, const wstring& path = L"");

private:
	vector<VertexTexture> vertices;
	vector<UINT> indices;

	ComPtr<ID3D11BlendState> blendState;

	char text[50] = "";
};