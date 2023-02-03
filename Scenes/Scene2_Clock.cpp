#include "stdafx.h"
#include "Scene2_Clock.h"

void Scene2::Init()
{
	clockCircle = make_unique<Circle>(WIN_CENTER, Vector2(gWinHeight / 1.15f, gWinHeight / 1.15f), 0.0f, 100.0f, WHITE);
	hourLine = make_unique<Line>(WIN_CENTER, gWinHeight / 4.0f, 0.0f, RED);
	minLine = make_unique<Line>(WIN_CENTER, gWinHeight / 3.0f, 0.0f, GREEN);
	secLine = make_unique<Line>(WIN_CENTER, gWinHeight / 2.5f, 0.0f, BLUE);
}

void Scene2::Destroy()
{
	secLine.reset();
	minLine.reset();	
	hourLine.reset();

	clockCircle.reset();
}

void Scene2::Update()
{
	GetLocalTime(&time);

	cout << time.wYear << "년 ";
	cout << time.wMonth << "월 ";
	cout << time.wDay << "일 ";
	
	switch (time.wDayOfWeek)
	{
	case 0:
		cout << "일요일 ";
		break;
	case 1:
		cout << "월요일 ";
		break;
	case 2:
		cout << "화요일 ";
		break;
	case 3:
		cout << "수요일 ";
		break;
	case 4:
		cout << "목요일 ";
		break;
	case 5:
		cout << "금요일 ";
		break;
	case 6:
		cout << "토요일 ";
		break;
	}
	cout << time.wHour << "시 ";
	cout << time.wMinute << "분 ";
	cout << time.wSecond << "초 ";
	cout << time.wMilliseconds << "밀리초" << '\n';

	hourLine->GetWorld()->SetRotation(time.wHour * 30.0f + time.wMinute * 30.0f / 60.0f + time.wSecond * 30.0f / 60.0f / 60.0f + time.wMilliseconds * 30.0f / 60.0f / 60.0f / 1000.f - 90);	
	minLine->GetWorld()->SetRotation(time.wMinute * 6.0f + time.wSecond * 6.0f / 60.0f + time.wMilliseconds * 6.0f / 60.0f / 1000.0f + - 90);
	secLine->GetWorld()->SetRotation(time.wSecond * 6.0f + time.wMilliseconds * 6.0f / 1000.0f + -90);

	clockCircle->Update();

	hourLine->Update();
	minLine->Update();
	secLine->Update();
}

void Scene2::Render()
{
	clockCircle->Render();

	hourLine->Render();
	minLine->Render();
	secLine->Render();
}
