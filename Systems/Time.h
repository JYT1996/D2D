#pragma once

class Time
{
	DECLARE_SINGLETON(Time);

//델타타임을 위한 싱클톤.
//델타타임이란 이전 프레임에서 다음 프레임으로 가는데 걸린 시간.
//업데이트에서 많은 메시지가 모이게 되면 작업이 느려질 수 있다.
//사용자의 하드웨어의 성능차이로 사용자마다 업데이트 속도의 차이가 발생할 수 있다. 
//그래서 성능이 좋으면 1초에 프레임이 80개이고, 성능이 좋지않으면 1초에 60프레임이 나올 때,
//프레임당 5만큼 도형을 옮길 경우, 유저마다 하드웨어 성능에 따라 차이가 생길 수 있다. 이를 방지하기 위해 델타타임을 사용한다.
//델타타임의 간격이 짧아서 프레임이 많을 경우 도형의 움직이는 속도를 늦추고, 델타타임의 간격이 길고 프레임이 적을 경우 도형의 움직이는 속도를 빠르게 한다.
//프레임을 많이 나왔다 해서 움직인 거리가 긴 것을 방지하고 프레임이 적게 나왔다 해서 움직인 거리가 짧지 않게 된다.

public:
	void Update();

	float GetDeltaTime() { return (float)deltaTime; }
	UINT GetFPS() { return fps; }
	double GetWorldTime() { return worldTime; }

	void CheckTime() { cout << "FPS : " << fps << ", DeltaTime : " << deltaTime << ", WorldTime : " << worldTime << '\n'; }

private:	//나노초단위로 특정 시간을 나타낸다.
	chrono::steady_clock::time_point currentTime;
	chrono::steady_clock::time_point lastTime;
	double deltaTime = 0.0f;

	UINT fps = 0;
	double worldTime = 0.0f;

	UINT frameCount = 0;
	double fpsTimeElapsed = 0.0;

};