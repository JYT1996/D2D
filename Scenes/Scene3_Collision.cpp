#include "stdafx.h"
#include "Scene3_Collision.h"

void Scene3::Init()
{
	rect1 = make_unique<ColorRect>(WIN_CENTER, Vector2(100, 100), 0.0f, BLUE);
	rect2 = make_unique<ColorRect>(WIN_CENTER + Vector2(300, 200), Vector2(100, 100), 20.0f);
	circle = make_unique<Circle>(Vector2(200, 200), Vector2(100, 100), 0.0f, 100, GREEN);
	filledCircle = make_unique<FilledCircle>(Vector2(200, 500), Vector2(100, 100), 0.0f, 100, CYAN);
}

void Scene3::Destroy()
{
	filledCircle.reset();
	circle.reset();
	rect2.reset();
	rect1.reset();
}

void Scene3::Update()
{
	if (INPUT->Down('Q'))
	{
		if (rect1->GetColorComp()->GetColor() == RED)
			rect1->GetColorComp()->SetColor(GREEN);
		else if (rect1->GetColorComp()->GetColor() == GREEN)
			rect1->GetColorComp()->SetColor(BLUE);
		else if (rect1->GetColorComp()->GetColor() == BLUE)
			rect1->GetColorComp()->SetColor(YELLOW);
		else if (rect1->GetColorComp()->GetColor() == YELLOW)
			rect1->GetColorComp()->SetColor(MAGENTA);
		else if (rect1->GetColorComp()->GetColor() == MAGENTA)
			rect1->GetColorComp()->SetColor(CYAN);
		else if (rect1->GetColorComp()->GetColor() == CYAN)
			rect1->GetColorComp()->SetColor(WHITE);
		else if (rect1->GetColorComp()->GetColor() == WHITE)
			rect1->GetColorComp()->SetColor(BLACK);
		else if (rect1->GetColorComp()->GetColor() == BLACK)
			rect1->GetColorComp()->SetColor(RED);
	}

	if (INPUT->Press('W'))
		rect1->GetWorld()->Move(Vector2(0, 300));
	if (INPUT->Press('S'))
		rect1->GetWorld()->Move(Vector2(0, -300));
	if (INPUT->Press('A'))
		rect1->GetWorld()->Move(Vector2(-300, 0));
	if (INPUT->Press('D'))
		rect1->GetWorld()->Move(Vector2(300, 0));

	if (INPUT->Press(VK_DOWN))
		rect1->GetWorld()->Scale(Vector2(-150, -150));
	if (INPUT->Press(VK_UP))
		rect1->GetWorld()->Scale(Vector2(150, 150));

	if (INPUT->Press(VK_LEFT))
		rect1->GetWorld()->Rotate(-200.0f);
	if (INPUT->Press(VK_RIGHT))
		rect1->GetWorld()->Rotate(200.0f);

	if (rect1->GetCollider()->Intersect(rect2->GetCollider()))
		rect2->GetColorComp()->SetColor(MAGENTA);
	else
		rect2->GetColorComp()->SetColor(RED);

	if (circle->GetCollider()->Intersect(rect1->GetCollider()))
		circle->GetColorComp()->SetColor(YELLOW);
	else
		circle->GetColorComp()->SetColor(GREEN);

	if (rect1->GetCollider()->Intersect(filledCircle->GetCollider()))
		filledCircle->GetColorComp()->SetColor(WHITE);
	else
		filledCircle->GetColorComp()->SetColor(CYAN);

	if (INPUT->Press(VK_LBUTTON) && rect1->GetCollider()->Intersect(INPUT->GetMousePosition()))
		rect1->GetWorld()->SetPosition(INPUT->GetMousePosition());

	rect1->Update();
	rect2->Update();
	circle->Update();
	filledCircle->Update();
}

void Scene3::Render()
{
	rect1->Render();
	rect2->Render();
	circle->Render();
	filledCircle->Render();
}
