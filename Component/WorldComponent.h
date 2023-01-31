#pragma once
//월드변환을 위한 기능을 담은 Component
class WorldComponent : public Component
{
public:
	WorldComponent(const Vector2& position, const Vector2& scale, const float rotation, const string& name = "World");

public:
	Vector2 GetPosition() const { return position; }
	Vector2 GetScale() const { return scale; }
	float GetRotation() const { return rotation; }
	float GetRotationDegree() const { return XMConvertToDegrees(rotation); }

	void SetPosition(const Vector2& position) { this->position = position; }
	void SetScale(const Vector2& scale) { this->scale = scale; }
	void SetRotation(const float& rotation) { this->rotation = XMConvertToRadians(rotation); }

	void Move(const Vector2& position) { this->position += position * TIME->GetDeltaTime(); }
	void Scale(const Vector2& scale) { this->scale += scale * TIME->GetDeltaTime(); }
	void Rotat(const float& rotation) { this->rotation += XMConvertToRadians(rotation) * TIME->GetDeltaTime(); }

public:
	void Update() override;
	void Render() override;

protected:
	unique_ptr<WorldBuffer> worldBuffer;
	Matrix world, S, R, T;

	Vector2 position, scale;
	float rotation = 0.0f;
};
