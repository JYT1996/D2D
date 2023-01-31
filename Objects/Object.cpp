#include "stdafx.h"
#include "Object.h"

void Object::AddComponent(const shared_ptr<Component>& component)
{
	if (components.count(component->GetName()))
		return;

	component->SetOwner(this);
	components.emplace(component->GetName(), component);
}

void Object::Update()
{
	for (const auto& comp : components)
		comp.second->Update();
}

void Object::Render()
{
	for (const auto& comp : components)
		comp.second->Render();
}
