#include "stdafx.h"
#include "ColorRect.h"

ColorRect::ColorRect()
{
	{
		vertices.assign(4, VertexColor());
		vertices[0].position = { -0.5f, -0.5f };
		vertices[0].color = { 1.0f, 0.0f, 0.f, 1.0f };
		vertices[1].position = { -0.5f, 0.5f };
		vertices[1].color = { 1.0f, 0.0f, 0.f, 1.0f };
		vertices[2].position = { 0.5f, -0.5f };
		vertices[2].color = { 1.0f, 0.0f, 0.f, 1.0f };
		vertices[3].position = { 0.5f, 0.5f };
		vertices[3].color = { 1.0f, 0.0f, 0.f, 1.0f };
	}

	{
		vertexBuffer.Create(vertices);
	}

	{
		vertexShader.Create(L"_Shaders/VertexColor.hlsl", "VS");
	}

	{
		indices = { 0, 1, 2, 2, 1, 3 };
	}

	{
		indexBuffer.Create(indices);
	}

	{
		inputLayout.Create(VertexColor::descs, VertexColor::count, vertexShader.GetBlob());
	}

	{
		pixelShader.Create(L"_Shaders/VertexColor.hlsl", "PS");
	}

	{		
		_degrees = -30.0f;
		cpuBuffer = make_unique<WorldBuffer>();		
		_scale = XMMatrixScaling(100, 100, 1);
		_rotation = XMMatrixRotationZ(XMConvertToRadians(_degrees));
		_translation = XMMatrixTranslation(WIN_DEFAULT_WIDTH / 2, WIN_DEFAULT_HEIGHT / 2, 0);
		SetWorldBuffer();
	}
}

void ColorRect::SetWorldBuffer()
{
	world = _scale * _rotation * _translation;
	cpuBuffer->SetWorld(world);
}

void ColorRect::SetCPUBuffer()
{
	cpuBuffer.get()->SetVSBuffer(0);
}

void ColorRect::Update()
{
	if (_keyCount == 2)
		_speed = _maxSpeed / sqrtf(2.0f);
	else
		_speed = _maxSpeed;
}

void ColorRect::Render()
{	
	vertexBuffer.SetIA();
	indexBuffer.SetIA();
	inputLayout.SetIA();
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	vertexShader.SetShader();
	pixelShader.SetShader();

	DC->DrawIndexed((UINT)indices.size(), 0, 0);
}
void ColorRect::Move(float x, float y, float z)
{
	SetTranslation(x, y, z);
}

void ColorRect::Rotate(float Degrees)
{	
	SetRotation(_degrees);
	_degrees += Degrees;
}

void ColorRect::Scale(float x, float y, float z)
{
	SetScale(x, y, z);
}
