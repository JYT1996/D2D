#pragma once
//interface
class Scene
{
public:
	virtual void Init() = 0;
	virtual void Destroy() = 0;

	virtual void Update() = 0;
	virtual void Render() = 0;

};