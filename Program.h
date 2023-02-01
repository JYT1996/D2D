#pragma once

class Program
{
public:
	Program();

public:
	void SetGlobalBuffer();

public:
	void Init();

	void Update();
	void Render();	

private:
	unique_ptr<ViewProjectiondBuffer> VPBuffer;

	Matrix view, projection;

	vector<shared_ptr<Scene>> sceneList;
	shared_ptr<Scene> currentScene;
};