#include "stdafx.h"
#include "Program.h"


Program::Program()
{
	VPBuffer = make_unique<ViewProjectiondBuffer>();	
	SetGlobalBuffer();

	rect = make_unique<ColorRect>("World", Vector2(WIN_CENTER_X, WIN_CENTER_Y), Vector2(100,100), 30.0f, L"_Shaders/VertexColor.hlsl");
}

void Program::SetGlobalBuffer()
{
	view = XMMatrixLookAtLH(Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(0, 1, 0));
	projection = XMMatrixOrthographicOffCenterLH(0, gWinWidth, 0, gWinHeight, 0, 1);

	VPBuffer->SetView(view);
	VPBuffer->SetProjection(projection);
}

void Program::Update()	//게임 로직의 메시지를 보내게 하는 것.world
{
	if (INPUT->Press('W'))		
		rect->GetComponent<WorldComponent>("World")->Move(Vector2(0, 300));
	if (INPUT->Press('S'))
		rect->GetComponent<WorldComponent>("World")->Move(Vector2(0, -300));
	if (INPUT->Press('A'))
		rect->GetComponent<WorldComponent>("World")->Move(Vector2(-300, 0));
	if (INPUT->Press('D'))
		rect->GetComponent<WorldComponent>("World")->Move(Vector2(300, 0));
	

	if (INPUT->Press('Q'))
		rect->GetComponent<WorldComponent>("World")->Rotat(-100);
	if (INPUT->Press('E'))
		rect->GetComponent<WorldComponent>("World")->Rotat(100);

	if (INPUT->Press('F'))
		rect->GetComponent<WorldComponent>("World")->Scale(Vector2(100,100));
	if (INPUT->Press('G'))
		rect->GetComponent<WorldComponent>("World")->Scale(Vector2(-100,-100));

	rect->Update();
}

void Program::Render()
{	
	rect->Render();
	VPBuffer.get()->SetVSBuffer(1);
	//렌더
}
