#pragma once

class Time
{
	DECLARE_SINGLETON(Time);

//��ŸŸ���� ���� ��Ŭ��.
//��ŸŸ���̶� ���� �����ӿ��� ���� ���������� ���µ� �ɸ� �ð�.
//������Ʈ���� ���� �޽����� ���̰� �Ǹ� �۾��� ������ �� �ִ�.
//������� �ϵ������ �������̷� ����ڸ��� ������Ʈ �ӵ��� ���̰� �߻��� �� �ִ�. 
//�׷��� ������ ������ 1�ʿ� �������� 80���̰�, ������ ���������� 1�ʿ� 60�������� ���� ��,
//�����Ӵ� 5��ŭ ������ �ű� ���, �������� �ϵ���� ���ɿ� ���� ���̰� ���� �� �ִ�. �̸� �����ϱ� ���� ��ŸŸ���� ����Ѵ�.
//��ŸŸ���� ������ ª�Ƽ� �������� ���� ��� ������ �����̴� �ӵ��� ���߰�, ��ŸŸ���� ������ ��� �������� ���� ��� ������ �����̴� �ӵ��� ������ �Ѵ�.
//�������� ���� ���Դ� �ؼ� ������ �Ÿ��� �� ���� �����ϰ� �������� ���� ���Դ� �ؼ� ������ �Ÿ��� ª�� �ʰ� �ȴ�.

public:
	void Update();

	float GetDeltaTime() { return (float)deltaTime; }
	UINT GetFPS() { return fps; }
	double GetWorldTime() { return worldTime; }

	void CheckTime() { cout << "FPS : " << fps << ", DeltaTime : " << deltaTime << ", WorldTime : " << worldTime << '\n'; }

private:	//�����ʴ����� Ư�� �ð��� ��Ÿ����.
	chrono::steady_clock::time_point currentTime;
	chrono::steady_clock::time_point lastTime;
	double deltaTime = 0.0f;

	UINT fps = 0;
	double worldTime = 0.0f;

	UINT frameCount = 0;
	double fpsTimeElapsed = 0.0;

};