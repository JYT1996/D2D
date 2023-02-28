#pragma once

class Time
{
	DECLARE_SINGLETON(Time);

public:
	void Update();

	float GetDeltaTime() { return (float)deltaTime; }
	UINT GetFPS() { return fps; }
	double GetWorldTime() { return worldTime; }

	void CheckTime() { cout << "FPS : " << fps << ", DeltaTime : " << deltaTime << ", WorldTime : " << worldTime << '\n'; }

private:
	chrono::steady_clock::time_point currentTime;
	chrono::steady_clock::time_point lastTime;
	double deltaTime = 0.0;

	UINT fps = 0;
	double worldTime = 0.0f;

	UINT frameCount = 0;
	double fpsTimeElapsed = 0.0;
};