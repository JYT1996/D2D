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

	if (GetKeyboardState(keyState))
	{
		for (DWORD i = 0; i < MAX_INPUT_KEY; ++i)
		{
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
	if (message >= WM_MOUSEFIRST && message <= WM_MOUSELAST)
	{
		mousePosition.x = (float)GET_X_LPARAM(lParam) * WIN_DEFAULT_WIDTH / gWinWidth;
		mousePosition.y = WIN_DEFAULT_HEIGHT - (float)GET_Y_LPARAM(lParam) * WIN_DEFAULT_HEIGHT / gWinHeight;

		//cout << "X : " << mousePosition.x << ", Y : " << mousePosition.y << '\n';

		if (message == WM_LBUTTONDBLCLK)
			isDblClk = true;
		else
			isDblClk = false;
	}
}
