#include "stdafx.h"
#include "Scene2_Clock.h"

void Scene2::Init()
{
	hourLine = make_unique<Line>(WIN_CENTER, 150, 270, RED);
	minLine = make_unique<Line>(WIN_CENTER, 220, 270, BLUE);
	secLine = make_unique<Line>(WIN_CENTER, 280, 270, GREEN);
	clockCircle = make_unique<Circle>(WIN_CENTER, Vector2(650, 650), 0, 100, WHITE);

}

void Scene2::Destroy()
{
	clockCircle.reset();
	secLine.reset();
	minLine.reset();
	hourLine.reset();
}

void Scene2::Update()
{
	GetLocalTime(&time);

	hourLine->GetWorld()->Rotat( 0.1 / 12);
	minLine->GetWorld()->Rotat( 0.1 );
	secLine->GetWorld()->Rotat( 6 );

	cout << time.wYear << "�� ";
	cout << time.wMonth << "�� ";
	cout << time.wDay << "�� ";
	
	switch (time.wDayOfWeek)
	{
	case 0:
		cout << "�Ͽ��� ";
		break;
	case 1:
		cout << "������ ";
		break;
	case 2:
		cout << "ȭ���� ";
		break;
	case 3:
		cout << "������ ";
		break;
	case 4:
		cout << "����� ";
		break;
	case 5:
		cout << "�ݿ��� ";
		break;
	case 6:
		cout << "����� ";
		break;
	}
	cout << time.wHour << "�� ";
	cout << time.wMinute << "�� ";
	cout << time.wSecond << "�� ";
	cout << time.wMilliseconds << "�и���" << '\n';

	if (INPUT->Down('Z'))
	{
		hourLine->GetWorld()->SetRotation((time.wHour % 12) * 30 + time.wMinute * 0.5 + time.wSecond * 0.5 / 60 + 270);
		minLine->GetWorld()->SetRotation(time.wMinute * 6 + time.wSecond * 0.1 + 270);
		secLine->GetWorld()->SetRotation(time.wSecond * 6 + 270);
	}

	hourLine->Update();
	minLine->Update();
	secLine->Update();
	clockCircle->Update();
}

void Scene2::Render()
{
	hourLine->Render();
	minLine->Render();
	secLine->Render();
	clockCircle->Render();
}
