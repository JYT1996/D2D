#pragma once

class ColorRect : public Drawable
{
public:
	ColorRect(const string& name, const Vector2& position, const Vector2& scale, const float& rotation, const wstring shaderPath);

public:
	void Update();
	void Render();

private:
	vector<VertexColor> vertices;
	vector<UINT> indices;
};
