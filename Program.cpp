#include "stdafx.h"
#include "Program.h"


Program::Program()
{
	VPBuffer = make_unique<ViewProjectiondBuffer>();	
	SetGlobalBuffer();

	rect = make_unique<ColorRect>(WIN_CENTER, Vector2(100.0f, 100.0f), 0.0f, RED);
	line = make_unique<Line>(WIN_CENTER, 300.0f, 0.0f, MAGENTA);
	circle = make_unique<Circle>(WIN_CENTER, Vector2(100, 100), 0.0f, RED);
	filledCircle = make_unique<FilledCircle>(WIN_CENTER, Vector2(100, 100), 0.0f, RED);
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
		line->GetWorld()->Move(Vector2(0, 300));
	if (INPUT->Press('S'))
		line->GetWorld()->Move(Vector2(0, -300));
	if (INPUT->Press('A'))
		line->GetWorld()->Move(Vector2(-300, 0));
	if (INPUT->Press('D'))
		line->GetWorld()->Move(Vector2(300, 0));
	
	if (INPUT->Press('Q'))
		line->GetWorld()->Rotat(-100);
	if (INPUT->Press('E'))
		line->GetWorld()->Rotat(100);

	if (INPUT->Press('F'))
		line->GetWorld()->Scale(Vector2(100,100));
	if (INPUT->Press('G'))
		line->GetWorld()->Scale(Vector2(-100,-100));

	if (INPUT->Press('Z'))
	{
		if(line->GetColorComp()->GetColor() == RED)
			line->GetColorComp()->SetColor(GREEN);
		else if(line->GetColorComp()->GetColor() == GREEN)
			line->GetColorComp()->SetColor(BLUE);
		else if (line->GetColorComp()->GetColor() == BLUE)
			line->GetColorComp()->SetColor(YELLOW);
		else if (line->GetColorComp()->GetColor() == YELLOW)
			line->GetColorComp()->SetColor(MAGENTA);
		else if (line->GetColorComp()->GetColor() == MAGENTA)
			line->GetColorComp()->SetColor(CYAN);
		else if (line->GetColorComp()->GetColor() == CYAN)
			line->GetColorComp()->SetColor(WHITE);
		else if (line->GetColorComp()->GetColor() == WHITE)
			line->GetColorComp()->SetColor(BLACK);
		else if (line->GetColorComp()->GetColor() == BLACK)
			line->GetColorComp()->SetColor(RED);
	}
	
	rect->Update();
	line->Update();
	//circle->Updata();
	//filledCircle->Updata();
}

void Program::Render()
{	
	VPBuffer.get()->SetVSBuffer(1);

	rect->Render();
	line->Render();
	//circle->Render();
	//filledCircle->Render();
	//·»´õ
}
