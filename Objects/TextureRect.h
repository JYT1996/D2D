#pragma once

class TextureRect : public Drawable
{
public:
	TextureRect(const Vector2& position, const Vector2& scale, const float& rotation, const wstring& texturePath = L"");
	TextureRect(const TextureRect& other) : TextureRect(other.GetWorld()->GetPosition(), other.GetWorld()->GetScale(), other.GetWorld()->GetRotation()) {}

public:
	void Update() override;
	void Render() override;

private:
	vector<VertexTexture> vertices;
	vector<UINT> indices;
};
