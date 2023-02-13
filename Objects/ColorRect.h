#pragma once

class ColorRect : public Drawable
{
public:
	ColorRect(const Vector2& position, const Vector2& scale, const float& rotation, const Color& color = RED);
	ColorRect(const ColorRect& other) : ColorRect(other.GetWorld()->GetPosition(), other.GetWorld()->GetScale(), other.GetWorld()->GetRotation(), other.GetColorComp()->GetColor()) {}

public:
	shared_ptr<ColorComponent> GetColorComp() const { return GetComponent<ColorComponent>("Color"); }

public:
	void Update();
	void Render();

private:
	vector<Vertex> vertices;
	vector<UINT> indices;
};
