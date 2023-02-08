#pragma once

#include "stdafx.h"

class Object; //stdafx에서 Component가 앞에 있고 Object가 뒤에 있기 때문에 선언을 해야 사용할 수 있다. 나중에 링커단계에서 합쳐지면서 문제가 발생하지 않는다.
class Component
{
public:
	Component(const string& compName) : name(compName) {}
	virtual ~Component() = default;
	
public:
	Object* GetOwner() const { return owner; }
	string GetName() const { return name; }

	void SetOwner(Object* obj) { owner = obj; }

public:
	virtual void Update() {};
	virtual void Render() {};

protected:
	string name;
	//기능이 추가된 객체.(부품을 가진 소유자)
	Object* owner = nullptr;
};
