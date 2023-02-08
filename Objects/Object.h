#pragma once

class Object
{
public:
	Object(const string& name) : name(name) {}
	virtual ~Object() = default;

public:
	void AddComponent(const shared_ptr<Component>& component);

	template<typename T>
	shared_ptr<T> GetComponent(const string& componentName) const
	{
		//���ҵ��� ������ ��ȯ ���ش�.
		if (!components.count(componentName))
			return nullptr;

		return dynamic_pointer_cast<T>(components.at(componentName));		
	}
public:
	shared_ptr<WorldComponent> GetWorld() const { return GetComponent<WorldComponent>("World"); }
	shared_ptr<ColliderComponent> GetCollider() const { return GetComponent<ColliderComponent>("Collider"); }

public:
	virtual void Update();
	virtual void Render();	

protected:
	string name;
	map<string, shared_ptr<Component>> components;
};
