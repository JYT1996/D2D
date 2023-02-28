#include "stdafx.h"
#include "Scene1_Geometry.h"

void Scene1::Init()
{
	rect = make_unique<ColorRect>(WIN_CENTER, Vector2(100, 100), 0.0f);
	line = make_unique<Line>(WIN_CENTER, 300.0f, 0.0f, MAGENTA);
	circle = make_unique<Circle>(WIN_CENTER, Vector2(100, 100), 0.0f, 100, YELLOW);
	filledCircle = make_unique<FilledCircle>(WIN_CENTER - Vector2(0, 100), Vector2(100, 100), 0.0f, 100, CYAN);
}

void Scene1::Destroy()
{
	filledCircle.reset();
	circle.reset();
	line.reset();
	rect.reset();
}

void Scene1::Update()
{
	if (INPUT->Down('Q'))
	{
		if (rect->GetColorComp()->GetColor() == RED)
			rect->GetColorComp()->SetColor(GREEN);
		else if (rect->GetColorComp()->GetColor() == GREEN)
			rect->GetColorComp()->SetColor(BLUE);
		else if (rect->GetColorComp()->GetColor() == BLUE)
			rect->GetColorComp()->SetColor(YELLOW);
		else if (rect->GetColorComp()->GetColor() == YELLOW)
			rect->GetColorComp()->SetColor(MAGENTA);
		else if (rect->GetColorComp()->GetColor() == MAGENTA)
			rect->GetColorComp()->SetColor(CYAN);
		else if (rect->GetColorComp()->GetColor() == CYAN)
			rect->GetColorComp()->SetColor(WHITE);
		else if (rect->GetColorComp()->GetColor() == WHITE)
			rect->GetColorComp()->SetColor(BLACK);
		else if (rect->GetColorComp()->GetColor() == BLACK)
			rect->GetColorComp()->SetColor(RED);
	}

	if (INPUT->Press('W'))
		rect->GetWorld()->Move(Vector2(0, 300));
	if (INPUT->Press('S'))
		rect->GetWorld()->Move(Vector2(0, -300));
	if (INPUT->Press('A'))
		rect->GetWorld()->Move(Vector2(-300, 0));
	if (INPUT->Press('D'))
		rect->GetWorld()->Move(Vector2(300, 0));

	rect->Update();
	line->Update();
	circle->Update();
	filledCircle->Update();
}

void Scene1::Render()
{
	rect->Render();
	line->Render();
	circle->Render();
	filledCircle->Render();
}
