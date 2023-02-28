#pragma once

#include "stdafx.h"

class Object;
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
	virtual void Update() {}
	virtual void Render() {}

protected:
	string name;
	Object* owner = nullptr;
};