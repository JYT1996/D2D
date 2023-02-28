#pragma once

class FilledCircle : public Drawable
{
public:
	FilledCircle(const Vector2& position, const Vector2& scale, const float& rotation, const size_t& segments, const Color& color = RED);
	FilledCircle(const FilledCircle& other) : FilledCircle(other.GetWorld()->GetPosition(), other.GetWorld()->GetScale(), other.GetWorld()->GetRotation(), other.segments, other.GetColorComp()->GetColor()) {}

public:
	shared_ptr<ColorComponent> GetColorComp() const { return GetComponent<ColorComponent>("Color"); }

public:
	void Update() override;
	void Render() override;

private:
	vector<Vertex> vertices;
	vector<UINT> indices;
	size_t segments = 0;
};