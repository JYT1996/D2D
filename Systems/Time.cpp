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
	//현재 시간을 대입한다
	currentTime = chrono::steady_clock::now();
	//현재 시간에 지난시간을 빼면 deltatIme이다.
	chrono::duration<double> delta = currentTime - lastTime;
	deltaTime = delta.count();	//duration을 실제 사용될 double로 바꿔야할 때 delta.count()를 사용한다.
	//현재 시간을 지난 시간에 대입한다.
	lastTime = currentTime;

	//실행시간을 표현 할 수 있다.
	worldTime += deltaTime;

	
	fpsTimeElapsed += deltaTime;
	//위에 작업이 끝나면 1프레임이다.
	++frameCount;

	if (fpsTimeElapsed > 1.0)	//현실시간 1초가 된다면.
	{
		fps = frameCount;		//여태 센 프레임이 fps가 된다.
		frameCount = 0;			//넣어주고 다시 fps를 계산하기 위해 0을 넣어준다.
		fpsTimeElapsed = 0.0;	//다음 1초를 계산하기 위해 0을 넣어준다.
		
		CheckTime();			//콘솔창으로 보기 편하기 때문에 콘솔창에 출력한다.
	}
}
