#include "stdafx.h"
#include "Program.h"


Program::Program()
{
	VPBuffer = make_unique<ViewProjectiondBuffer>();	
	SetGlobalBuffer();

	rect = make_unique<ColorRect>(Vector2(WIN_CENTER_X, WIN_CENTER_Y), Vector2(100,100), 30.0f);
	line = make_unique<Line>(Vector2(WIN_CENTER_X, WIN_CENTER_Y), Vector2(100, 100), 30.0f);
	circle = make_unique<Circle>(Vector2(WIN_CENTER_X, WIN_CENTER_Y), Vector2(100, 100), 0.0f);
	filledCircle = make_unique<FilledCircle>(Vector2(WIN_CENTER_X, WIN_CENTER_Y), Vector2(100, 100), 0.0f);
}

void Program::SetGlobalBuffer()
{
	view = XMMatrixLookAtLH(Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(0, 1, 0));
	projection = XMMatrixOrthographicOffCenterLH(0, gWinWidth, 0, gWinHeight, 0, 1);

	VPBuffer->SetView(view);
	VPBuffer->SetProjection(projection);
}

void Program::Update()
{
	if (INPUT->Press('W'))		
		filledCircle->GetWorld()->Move(Vector2(0, 300));
	if (INPUT->Press('S'))
		filledCircle->GetWorld()->Move(Vector2(0, -300));
	if (INPUT->Press('A'))
		filledCircle->GetWorld()->Move(Vector2(-300, 0));
	if (INPUT->Press('D'))
		filledCircle->GetWorld()->Move(Vector2(300, 0));
	
	if (INPUT->Press('Q'))
		filledCircle->GetWorld()->Rotat(-100);
	if (INPUT->Press('E'))
		filledCircle->GetWorld()->Rotat(100);

	if (INPUT->Press('F'))
		filledCircle->GetWorld()->Scale(Vector2(100,100));
	if (INPUT->Press('G'))
		filledCircle->GetWorld()->Scale(Vector2(-100,-100));

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

	
	//rect->Update();
	//line->Updata();
	//circle->Updata();
	filledCircle->Updata();
}

void Program::Render()
{	
	//rect->Render();
	//line->Render();
	//circle->Render();
	filledCircle->Render();
	VPBuffer.get()->SetVSBuffer(1);
	//·»´õ
}
