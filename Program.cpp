#include "stdafx.h"
#include "Scenes/SceneList.h"
#include "Program.h"

Program::Program()
{
}

void Program::Init()
{
	//sceneList.push_back(make_shared<Scene1>());
	//sceneList.push_back(make_shared<Scene2>());
	//sceneList.push_back(make_shared<Scene3>());
	//sceneList.push_back(make_shared<Scene4>());
	//sceneList.push_back(make_shared<Scene5>());
	//sceneList.push_back(make_shared<Scene6>());
	sceneList.push_back(make_shared<Scene7>());
	sceneList.push_back(make_shared<Scene8>());
	sceneList.push_back(make_shared<Scene9>());

	currentScene = sceneList[2];
	currentScene->Init();
}

void Program::Update()
{
	if (INPUT->Down(VK_F1))
	{
		currentScene->Destroy();
		currentScene = sceneList[0];
		currentScene->Init();
	}
	else if (INPUT->Down(VK_F2))
	{
		currentScene->Destroy();
		currentScene = sceneList[1];
		currentScene->Init();
	}
	else if (INPUT->Down(VK_F3))
	{
		currentScene->Destroy();
		currentScene = sceneList[2];
		currentScene->Init();
	}

	CAMERA->Update();

	currentScene->Update();
}

void Program::PreRender()
{
	currentScene->PreRender();
}

void Program::Render()
{
	CAMERA->Render();

	currentScene->Render();
}

void Program::PostRender()
{
	currentScene->PostRender();

	IMGUI->PrintFrame();
}
