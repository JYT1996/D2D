#include "stdafx.h"
#include "Scenes/SceneList.h"
#include "Program.h"

Program::Program()
{
	VPBuffer = make_unique<ViewProjectiondBuffer>();	

	SetGlobalBuffers();
}

void Program::SetGlobalBuffers()
{
	view = XMMatrixLookAtLH(Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(0, 1, 0));
	projection = XMMatrixOrthographicOffCenterLH(0, WIN_DEFAULT_WIDTH, 0, WIN_DEFAULT_HEIGHT, 0, 1);

	VPBuffer->SetView(view);
	VPBuffer->SetProjection(projection);
}

void Program::Init()
{
	//sceneList.push_back(make_shared<Scene1>());
	//sceneList.push_back(make_shared<Scene2>());
	//sceneList.push_back(make_shared<Scene3>());
	//sceneList.push_back(make_shared<Scene4>());
	sceneList.push_back(make_shared<Scene5>());
	sceneList.push_back(make_shared<Scene6>());
	sceneList.push_back(make_shared<Scene7>());

	currentScene = sceneList[2];
	currentScene->Init();
}

void Program::Update()
{
	if (INPUT->Down(VK_F1))
	{
		currentScene = sceneList[0];
		currentScene->Init();
	}
	else if (INPUT->Down(VK_F2))
	{
		currentScene = sceneList[1];
		currentScene->Init();
	}
	else if (INPUT->Down(VK_F3))
	{
		currentScene = sceneList[2];
		currentScene->Init();
	}

	currentScene->Update();
}

void Program::PreRender()
{
	currentScene->PreRender();
}

void Program::Render()
{	
	VPBuffer->SetVSBuffer(1);

	currentScene->Render();
}

void Program::PostRender()
{
	currentScene->PostRender();

	IMGUI->PrintFrame();
}
