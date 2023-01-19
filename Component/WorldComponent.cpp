#include "stdafx.h"
#include "WorldComponent.h"
//월드 변환을 위한 준비를 한다.
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
