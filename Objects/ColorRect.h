#pragma once

class ColorRect
{
public:
	ColorRect();
	~ColorRect() {};

public:
	void SetWorldBuffer();
	void SetCPUBuffer();

	void Update();
	void Render();

	void Move(float x, float y, float z);
	void Rotate(float _degrees);
	void Scale(float x, float y, float z);

	float GetSpeed() const { return _speed; }
	void SetSpeed(float speed) { this->_speed = _speed; }
	void SetMaxSeed(float maxSpeed) { this->_maxSpeed = _maxSpeed; };

	void SetScale(float x, float y, float z)	{ _scale = XMMatrixScaling(_scale._11 + x, _scale._22 + y, _scale._33 + z ); };
	void SetRotation(float Degrees) { _rotation = XMMatrixRotationZ(XMConvertToRadians(Degrees)); };
	void SetTranslation(float x, float y, float z) { _translation = XMMatrixTranslation(_translation._41 + x, _translation._42 + y, _translation._43 + z); };

	void AddKeyCount() { ++_keyCount; }
	void ResetKeyCount() { _keyCount = 0; }

private:
	vector<VertexColor> vertices;
	VertexBuffer vertexBuffer;

	vector<UINT> indices;
	IndexBuffer indexBuffer;

	VertexShader vertexShader;

	InputLayout inputLayout;

	PixelShader pixelShader;

	unique_ptr<WorldBuffer> cpuBuffer;
	Matrix world;
	Matrix _scale, _rotation, _translation;

	ComPtr<ID3D11RasterizerState> RS;

	float _degrees = 0.0f;

	float _speed = 0.0f;
	float _maxSpeed = 200.0f;

	int _keyCount = 0;
};
