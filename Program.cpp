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

	currentScene = sceneList[0];
	//�����ڿ��� ���� init�� ���� Ȱ���ϸ�,
	//�ʱ�ȭ�� ���� �� ����� �� �ִ�.
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

	currentScene->Update();
}

void Program::Render()
{	
	VPBuffer.get()->SetVSBuffer(1);

	currentScene->Render();
}
