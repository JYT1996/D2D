#include "stdafx.h"
#include "WorldComponent.h"

WorldComponent::WorldComponent(const Vector2& position, const Vector2& scale, const float rotation, const string& name)
	:Component(name), position(position), scale(scale), rotation(XMConvertToRadians(rotation))
{
	worldBuffer = make_unique<WorldBuffer>();
}

void WorldComponent::Updata()
{
	S = XMMatrixScalingFromVector(scale);
	R = XMMatrixRotationZ(-rotation);
	T = XMMatrixTranslationFromVector(position);

	world = S * R * T;
	worldBuffer->SetWorld(world);
}

void WorldComponent::Render()
{
	worldBuffer->SetVSBuffer(0);
}
