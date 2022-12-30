#include "stdafx.h"
#include "Time.h"

Time::Time()
{
	
	currentTime = chrono::steady_clock::now();
	
	lastTime = currentTime;
}

Time::~Time() {}

void Time::Updata()
{
	//���� �ð��� �����Ѵ�
	currentTime = chrono::steady_clock::now();
	//���� �ð��� �����ð��� ���� deltatIme�̴�.
	chrono::duration<double> delta = currentTime - lastTime;
	deltaTime = delta.count();	//duration�� ���� ���� double�� �ٲ���� �� delta.count()�� ����Ѵ�.
	//���� �ð��� ���� �ð��� �����Ѵ�.
	lastTime = currentTime;

	//����ð��� ǥ�� �� �� �ִ�.
	worldTime += deltaTime;

	
	fpsTimeElapsed += deltaTime;
	//���� �۾��� ������ 1�������̴�.
	++frameCount;

	if (fpsTimeElapsed > 1.0)	//���ǽð� 1�ʰ� �ȴٸ�.
	{
		fps = frameCount;		//���� �� �������� fps�� �ȴ�.
		frameCount = 0;			//�־��ְ� �ٽ� fps�� ����ϱ� ���� 0�� �־��ش�.
		fpsTimeElapsed = 0.0;	//���� 1�ʸ� ����ϱ� ���� 0�� �־��ش�.
		
		CheckTime();			//�ܼ�â���� ���� ���ϱ� ������ �ܼ�â�� ����Ѵ�.
	}
}
