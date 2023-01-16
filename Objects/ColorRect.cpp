#include "stdafx.h"
#include "ColorRect.h"

ColorRect::ColorRect(Vector3 scale, float rotation, Vector3 translation)
	:scale(scale), rotation(rotation), translation(translation)
{
	vertices.assign(4, VertexColor());
	vertices[0].position = { 0.0f, 1.0f };
	vertices[0].color = { 1.0f, 0.0f, 0.f, 1.0f };
	vertices[1].position = { 0.0f, 0.0f };
	vertices[1].color = { 1.0f, 0.0f, 0.f, 1.0f };
	vertices[2].position = { 1.0f, 1.0f };
	vertices[2].color = { 1.0f, 0.0f, 0.f, 1.0f };
	vertices[3].position = { 1.0f, 0.0f };
	vertices[3].color = { 1.0f, 0.0f, 0.f, 1.0f };

	vertexBuffer.Create(vertices);

	vertexShader.Create(L"_Shaders/Color.hlsl", "VS");

	indices = { 0, 1, 2, 2, 1, 3 };
	indexBuffer.Create(indices);

	inputLayout.Create(vertexColor.descs, vertexColor.count, inputLayout.GetResource());

	pixelShader.Create(L"_Shaders/Color.hlsl", "PS");

	Matrix S, R, T;
	S = XMMatrixScaling(scale.x, scale.y, scale.z);
	R = XMMatrixRotationZ(XMConvertToRadians(rotation));
	T = XMMatrixTranslation(translation.x, translation.y, translation.z);

	world = S * R * T;
}

ColorRect* ColorRect::GetColorRect()
{
	return this;
}

void ColorRect::SetColorRect()
{
	
}

void ColorRect::Move(Vector3 translation)
{
	this->translation += translation;
}

void ColorRect::Rotate(float rotation)
{
	this->rotation += rotation;
}

void ColorRect::Scale(Vector3 scale)
{
	this->scale += scale;
}
