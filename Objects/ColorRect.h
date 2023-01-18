#pragma once

class ColorRect
{
public:
	ColorRect(const Vector2& position, const Vector2& scale, const float& rotation);

public:
	void Update();
	void Render();

	Vector2 GetPosition() const { return position; }
	Vector2 GetScale() const { return scale; }
	float GetRotation() const { return rotation; }
	float GetRotationDegree() const { return XMConvertToDegrees(rotation); }

	void SetPosition(const Vector2& position) { this->position = position; }
	void SetScale(const Vector2& scale) { this->scale = scale; }
	void SetRotation(const float& rotation) { this->rotation = XMConvertToRadians(rotation); }

	void Move(const Vector2& position) {  this->position += position *TIME->GetDeltaTime(); }
	void Scale(const Vector2& scale) { this->scale += scale * TIME->GetDeltaTime(); }
	void Rotat(const float& rotation) { this->rotation += XMConvertToRadians(rotation) * TIME->GetDeltaTime(); }

private:
	vector<VertexColor> vertices;
	vector<UINT> indices;

	unique_ptr<VertexBuffer> vertexBuffer;	
	unique_ptr<VertexShader> vertexShader;
	unique_ptr<IndexBuffer> indexBuffer;
	unique_ptr<InputLayout> inputLayout;

	unique_ptr<PixelShader> pixelShader;

	unique_ptr<WorldBuffer> worldBuffer;
	Matrix world, S, R, T;

	Vector2 position, scale;
	float rotation = 0.0f;
};
