#include "stdafx.h"
#include "Scene1_Geometry.h"

void Scene1::Init()
{
	rect = make_unique<ColorRect>(WIN_CENTER, Vector2(100.0f, 100.0f), 0.0f);
	rect2 = make_unique<Line>(WIN_CENTER, 300.0f, 0.0f, MAGENTA);
	circle = make_unique<Circle>(WIN_CENTER, Vector2(100, 100), 0.0f, 100, YELLOW);
	filledCircle = make_unique<FilledCircle>(WIN_CENTER - Vector2(0, 100), Vector2(100, 100), 0.0f, 100, CYAN);
}

void Scene1::Destroy()
{
	filledCircle.reset();
	circle.reset();
	rect2.reset();
	rect.reset();
}

void Scene1::Update()
{
	if (INPUT->Press('W'))
		circle->GetWorld()->Move(Vector2(0, 300));
	if (INPUT->Press('S'))
		circle->GetWorld()->Move(Vector2(0, -300));
	if (INPUT->Press('A'))
		circle->GetWorld()->Move(Vector2(-300, 0));
	if (INPUT->Press('D'))
		circle->GetWorld()->Move(Vector2(300, 0));

	if (INPUT->Press('Q'))
		circle->GetWorld()->Rotat(-100);
	if (INPUT->Press('E'))
		circle->GetWorld()->Rotat(100);

	if (INPUT->Press('F'))
		circle->GetWorld()->Scale(Vector2(100, 100));
	if (INPUT->Press('G'))
		circle->GetWorld()->Scale(Vector2(-100, -100));

	if (INPUT->Down('Z'))
	{
		if (circle->GetColorComp()->GetColor() == RED)
			circle->GetColorComp()->SetColor(GREEN);
		else if (circle->GetColorComp()->GetColor() == GREEN)
			circle->GetColorComp()->SetColor(BLUE);
		else if (circle->GetColorComp()->GetColor() == BLUE)
			circle->GetColorComp()->SetColor(YELLOW);
		else if (circle->GetColorComp()->GetColor() == YELLOW)
			circle->GetColorComp()->SetColor(MAGENTA);
		else if (circle->GetColorComp()->GetColor() == MAGENTA)
			circle->GetColorComp()->SetColor(CYAN);
		else if (circle->GetColorComp()->GetColor() == CYAN)
			circle->GetColorComp()->SetColor(WHITE);
		else if (circle->GetColorComp()->GetColor() == WHITE)
			circle->GetColorComp()->SetColor(BLACK);
		else if (circle->GetColorComp()->GetColor() == BLACK)
			circle->GetColorComp()->SetColor(RED);
	}

	rect->Update();
	rect2->Update();
	circle->Update();
	filledCircle->Update();
}

void Scene1::Render()
{
	rect->Render();
	rect2->Render();
	circle->Render();
	filledCircle->Render();
}
