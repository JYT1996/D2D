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

	}

protected:
	string name;
	map<string, shared_ptr<Component>> components;
};
