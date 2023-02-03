#include "stdafx.h"
#include "Scenes/SceneList.h"
#include "Program.h"


Program::Program()
{
	VPBuffer = make_unique<ViewProjectiondBuffer>();	

	SetGlobalBuffer();
}

void Program::SetGlobalBuffer()
{
	view = XMMatrixLookAtLH(Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(0, 1, 0));
	projection = XMMatrixOrthographicOffCenterLH(0, gWinWidth, 0, gWinHeight, 0, 1);

	VPBuffer->SetView(view);
	VPBuffer->SetProjection(projection);
}

void Program::Init()
{
	sceneList.push_back(make_shared<Scene1>());
	sceneList.push_back(make_shared<Scene2>());
	sceneList.push_back(make_shared<Scene3>());

	currentScene = sceneList[2];
	//생성자에서 따로 init을 빼서 활용하면,
	//초기화를 원할 때 사용할 수 있다.
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

	currentScene->Update();
}

void Program::Render()
{	
	VPBuffer.get()->SetVSBuffer(1);

	currentScene->Render();
}
