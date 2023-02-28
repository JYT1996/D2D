#include "stdafx.h"
#include "WorldComponent.h"

WorldComponent::WorldComponent(const Vector2& position, const Vector2& scale, const float& rotation, const string& name)
	: Component(name), position(position), scale(scale), rotation(XMConvertToRadians(rotation))
{
	WB = make_unique<WorldBuffer>();
}

void WorldComponent::Update()
{
	S = XMMatrixScalingFromVector(scale);
	R = XMMatrixRotationZ(-rotation);
	T = XMMatrixTranslationFromVector(position);

	world = S * R * T;

	WB->SetWorld(world);
}

void WorldComponent::Render()
{
	WB->SetVSBuffer(0);
}

void WorldComponent::GUI()
{
	ImGui::SliderFloat2("Translation", (float*)&position, 0, gWinWidth, "%.2f");
	ImGui::SliderFloat2("Scale", (float*)&scale, 1, gWinWidth, "%.2f");
	ImGui::SliderAngle("Rotation", &rotation);
}
