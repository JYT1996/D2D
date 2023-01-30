 #pragma once

class FilledCircle : public Drawable
{
public:
	FilledCircle(const Vector2& position, const Vector2& scale, const float& rotation, Color color = RED);

public:
	void Update();
	void Render();

public:
	Color GetColor() const { return color; }
	void SetColor(Color color);

private:
	vector<VertexColor> vertices;
	vector<UINT> indices;

	Color color;
};
