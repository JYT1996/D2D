#pragma once

class Line : public Drawable
{
public:
	Line(const Vector2& position, const float& length, const float& rotation, const Color& color = RED);
	Line(const Line& other) : Line(other.GetWorld()->GetPosition(), other.GetWorld()->GetScale().x, other.GetWorld()->GetRotation(), other.GetColorComp()->GetColor()){}
	
public:
	shared_ptr<ColorComponent> GetColorComp() const { return GetComponent<ColorComponent>("Color"); }

public:
	void Update() override;
	void Render() override;

private:
	vector<Vertex> vertices;
};
