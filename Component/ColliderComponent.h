#pragma once

enum class ColliderType
{
	NONE,
	RECT,
	CIRCLE,
};

class ColliderComponent : public Component
{
public:
	ColliderComponent(const ColliderType& type = ColliderType::NONE, const string& name = "Collider") : Component(name), type(type)	{}

public:
	//object�� ���� �浹(���콺 �浹)
	bool intersect(const Vector2& coord);
	//Collider�� ���� object�� �浹
	bool intersect(const shared_ptr<ColliderComponent>& other);

private:
	ColliderType type = ColliderType::NONE;
};