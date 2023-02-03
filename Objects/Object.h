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
		//원소들의 갯수를 반환 해준다.
		if (!components.count(componentName))
			return nullptr;

		return dynamic_pointer_cast<T>(components.at(componentName));		
	}
public:
	shared_ptr<WorldComponent> GetWorld() const { return GetComponent<WorldComponent>("World"); }

public:
	virtual void Update();
	virtual void Render();	

protected:
	string name;
	map<string, shared_ptr<Component>> components;
};
