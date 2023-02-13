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
	shared_ptr<TextureComponent> GetTexture() const { return GetComponent<TextureComponent>("Texture"); }

private:
	vector<VertexTexture> vertices;
	vector<UINT> indices;
};
