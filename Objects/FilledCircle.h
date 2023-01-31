 #pragma once

class FilledCircle : public Drawable
{
public:
	FilledCircle(const Vector2& position, const Vector2& scale, const float& rotation, const Color& color = RED);

public:
	shared_ptr<ColorComponent> GetColorComp() { return GetComponent<ColorComponent>("Color"); }

public:
	void Update();
	void Render();

private:
	vector<Vertex> vertices;
	vector<UINT> indices;
};
