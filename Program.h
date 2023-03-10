#pragma once

class Program
{
public:
	Program();

public:
	void Init();

	void Update();
	void PreRender();
	void Render();
	void PostRender();

private:
	vector<shared_ptr<Scene>> sceneList;
	shared_ptr<Scene> currentScene;
};