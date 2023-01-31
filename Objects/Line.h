#pragma once

class Line : public Drawable
{
public:
	Line(const Vector2& position, const float& length, const float& rotation, const Color& color = RED);

public:
	shared_ptr<ColorComponent> GetColorComp() { return GetComponent<ColorComponent>("Color"); }

public:
	void Update() override;
	void Render() override;

private:
	vector<Vertex> vertices;
};
