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
	//object와 점의 충돌(마우스 충돌)
	bool intersect(const Vector2& coord);
	//Collider을 가진 object의 충돌
	bool intersect(const shared_ptr<ColliderComponent>& other);

private:
	ColliderType type = ColliderType::NONE;
};