#pragma once

class WorldComponent : public Component
{
public:
	WorldComponent(const Vector2& position, const Vector2& scale, const float& rotation, const string& name = "World");

public:
	Vector2 GetPosition() const { return position; }
	Vector2 GetScale() const { return scale; }
	float GetRotation() const { return rotation; }
	float GetRotationDegree() const { return XMConvertToDegrees(rotation); }
	Vector2 GetUpVector() const { return Vector2((R * T)._21, (R * T)._22); }
	Vector2 GetRightVector() const { return Vector2((R * T)._11, (R * T)._12); }
	Matrix GetS() const { return S; }
	Matrix GetR() const { return R; }
	Matrix GetT() const { return T; }

	void SetPosition(const Vector2& position) { this->position = position; }
	void SetScale(const Vector2& scale) { this->scale = scale; }
	void SetRotation(const float& rotation) { this->rotation = XMConvertToRadians(rotation); }
	void SetWorld(const Matrix& world)
	{
		this->world = world;
		WB->SetWorld(world);
	}

	void Move(const Vector2& position) { this->position += position * TIME->GetDeltaTime(); }
	void Scale(const Vector2& scale) { this->scale += scale * TIME->GetDeltaTime(); }
	void Rotate(const float& rotation) { this->rotation += XMConvertToRadians(rotation) * TIME->GetDeltaTime(); }

public:
	void Update() override;
	void Render() override;

public:
	void GUI();

private:
	unique_ptr<WorldBuffer> WB;
	Matrix world, S, R, T;

	Vector2 position, scale;
	float rotation = 0.0f;
};