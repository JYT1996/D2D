#include "stdafx.h"
#include "Input.h"

Input::Input()
{
	ZeroMemory(keyState, sizeof(keyState));
	ZeroMemory(keyOldState, sizeof(keyOldState));
	ZeroMemory(keyMap, sizeof(keyMap));
}
Input::~Input() {}

void Input::Update()
{
	memcpy(keyOldState, keyState, sizeof(keyOldState));

	ZeroMemory(keyState, sizeof(keyState));
	ZeroMemory(keyMap, sizeof(keyMap));

	/*GetKeyboardState() 256개 가상키의 상태를 받아온다.
	 업데이트 주기가 다르기 때문에 그대로 사용할 수가 없다.
	0x00
	이전에 누르지도 않았고 호출도 하지 않은 상태.

	0x01
	이전에 누른적이 있고 호출시점에는 눌려있지 않은 상태.

	0x80(이것이 중요)
	이전에 누른적이 없고 호출시점에는 눌려있는 상태.

	0x81
	이전에 누른적이 있고 호출시점에도 눌려있는 상태.
	*/
	if (GetKeyboardState(keyState))
	{
		for (DWORD i = 0; i < MAX_INPUT_KEY; ++i)
		{
			//이진법으로 1000 0000 을 키로 누른것으러 인식하고 1을 대입. 1000 0000이 아니면 0으로 인식
			keyState[i] = keyState[i] & 0x80 ? 1 : 0;

			unsigned char& oldState = keyOldState[i];
			unsigned char& state = keyState[i];

			if (oldState == 0 && state == 1)
				keyMap[i] = KEY_INPUT_STATUS_DOWN;
			else if (oldState == 1 && state == 0)
				keyMap[i] = KEY_INPUT_STATUS_UP;
			else if (oldState == 1 && state == 1)
				keyMap[i] = KEY_INPUT_STATUS_PRESS;
			else
				keyMap[i] = KEY_INPUT_STATUS_NONE;
		}
	}
}

void Input::InputProc(UINT message, LPARAM lParam)
{
	//마우스의 입력에 관한 시작점과 마지막을 통해서 마우스 입력을 구분한다.
	if (message >= WM_MOUSEFIRST && message <= WM_MOUSELAST)
	{
		//DX는 투영변환을 하기 때문에 윈도우창의 비율이 바뀌면 마우스의 값이 대응이 안될 수 있다.
		//그래서 정규화를 해서 창의 크기가 바뀌더라도 대응할 수 있게 한다.
		mousePosition.x = (float)GET_X_LPARAM(lParam) * WIN_DEFAULT_WIDTH / gWinWidth;
		//윈도우API와 DX는 Y좌표가 반대이다.
		mousePosition.y = WIN_DEFAULT_HEIGHT - (float)GET_Y_LPARAM(lParam) * WIN_DEFAULT_HEIGHT / gWinHeight;
		//cout << "X : " << mousePosition.x << ", Y : " << mousePosition.y << '\n';

		//좌클릭의 더블클릭만 구현.
		if (message == WM_LBUTTONDBLCLK)
			isDblClk = true;
		else
			isDblClk = false;
	}
}
