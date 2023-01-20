#include "stdafx.h"
#include "Program.h"


Program::Program()
{
	VPBuffer = make_unique<ViewProjectiondBuffer>();	
	SetGlobalBuffer();

	rect = make_unique<ColorRect>(Vector2(WIN_CENTER_X, WIN_CENTER_Y), Vector2(100,100), 30.0f);
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
		rect->GetWorld()->Move(Vector2(0, 300));
	if (INPUT->Press('S'))
		rect->GetWorld()->Move(Vector2(0, -300));
	if (INPUT->Press('A'))
		rect->GetWorld()->Move(Vector2(-300, 0));
	if (INPUT->Press('D'))
		rect->GetWorld()->Move(Vector2(300, 0));
	
	if (INPUT->Press('Q'))
		rect->GetWorld()->Rotat(-100);
	if (INPUT->Press('E'))
		rect->GetWorld()->Rotat(100);

	if (INPUT->Press('F'))
		rect->GetWorld()->Scale(Vector2(100,100));
	if (INPUT->Press('G'))
		rect->GetWorld()->Scale(Vector2(-100,-100));

	if (INPUT->Press('Z'))
	{
		if(rect->GetColor() == RED)
			rect->SetColor(GREEN);
		else if(rect->GetColor() == GREEN)
			rect->SetColor(BLUE);
		else if (rect->GetColor() == BLUE)
			rect->SetColor(YELLOW);
		else if (rect->GetColor() == YELLOW)
			rect->SetColor(MAGENTA);
		else if (rect->GetColor() == MAGENTA)
			rect->SetColor(CYAN);
		else if (rect->GetColor() == CYAN)
			rect->SetColor(WHITE);
		else if (rect->GetColor() == WHITE)
			rect->SetColor(BLACK);
		else if (rect->GetColor() == BLACK)
			rect->SetColor(RED);
	}

	rect->Update();
}

void Program::Render()
{	
	rect->Render();
	VPBuffer.get()->SetVSBuffer(1);
	//렌더
}
