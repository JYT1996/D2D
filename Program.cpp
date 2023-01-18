#include "stdafx.h"
#include "Program.h"


Program::Program()
{
	VPBuffer = make_unique<ViewProjectiondBuffer>();	
	SetGlobalBuffer();
	rect = make_unique<ColorRect>();
}

Program::~Program()
{

}

void Program::SetGlobalBuffer()
{
	view = XMMatrixLookAtLH(Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(0, 1, 0));
	projection = XMMatrixOrthographicOffCenterLH(0, WIN_DEFAULT_WIDTH, 0, WIN_DEFAULT_HEIGHT, 0, 1);

	VPBuffer->SetView(view);
	VPBuffer->SetProjection(projection);
}

void Program::Update()	//게임 로직의 메시지를 보내게 하는 것.
{
	rect->SetWorldBuffer();
	rect->SetCPUBuffer();
	VPBuffer.get()->SetVSBuffer(1);

	rect->ResetKeyCount();
	if (INPUT->Press('W'))
	{
		rect->AddKeyCount();
		rect->Move(0, rect->GetSpeed() * TIME->GetDeltaTime(), 0);
	}
	if (INPUT->Press('S'))
	{
		rect->AddKeyCount();
		rect->Move(0, -rect->GetSpeed() * TIME->GetDeltaTime(), 0);
	}
	if (INPUT->Press('A'))
	{
		rect->AddKeyCount();
		rect->Move(-rect->GetSpeed() * TIME->GetDeltaTime(), 0, 0);
	}
	if (INPUT->Press('D'))
	{
		rect->AddKeyCount();
		rect->Move(rect->GetSpeed() * TIME->GetDeltaTime(), 0, 0);
	}
	if (INPUT->Press('Q'))
	{
		rect->Rotate(-40 * TIME->GetDeltaTime());
	}
	if (INPUT->Press('E'))
	{
		rect->Rotate(40 * TIME->GetDeltaTime());
	}
	if (INPUT->Press('F'))
	{
		rect->Scale(100 * TIME->GetDeltaTime(), 100 * TIME->GetDeltaTime(), 0);
	}
	if (INPUT->Press('G'))
	{
		rect->Scale(-100 * TIME->GetDeltaTime(), -100 * TIME->GetDeltaTime(), 0);
	}
	rect->Update();
}

void Program::Render()
{		
	rect.get()->Render();
	//렌더
}
