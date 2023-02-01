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

	/*GetKeyboardState() 256�� ����Ű�� ���¸� �޾ƿ´�.
	 ������Ʈ �ֱⰡ �ٸ��� ������ �״�� ����� ���� ����.
	0x00
	������ �������� �ʾҰ� ȣ�⵵ ���� ���� ����.

	0x01
	������ �������� �ְ� ȣ��������� �������� ���� ����.

	0x80(�̰��� �߿�)
	������ �������� ���� ȣ��������� �����ִ� ����.

	0x81
	������ �������� �ְ� ȣ��������� �����ִ� ����.
	*/
	if (GetKeyboardState(keyState))
	{
		for (DWORD i = 0; i < MAX_INPUT_KEY; ++i)
		{
			//���������� 1000 0000 �� Ű�� ���������� �ν��ϰ� 1�� ����. 1000 0000�� �ƴϸ� 0���� �ν�
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
	//���콺�� �Է¿� ���� �������� �������� ���ؼ� ���콺 �Է��� �����Ѵ�.
	if (message >= WM_MOUSEFIRST && message <= WM_MOUSELAST)
	{
		//DX�� ������ȯ�� �ϱ� ������ ������â�� ������ �ٲ�� ���콺�� ���� ������ �ȵ� �� �ִ�.
		//�׷��� ����ȭ�� �ؼ� â�� ũ�Ⱑ �ٲ���� ������ �� �ְ� �Ѵ�.
		mousePosition.x = (float)GET_X_LPARAM(lParam) * WIN_DEFAULT_WIDTH / gWinWidth;
		//������API�� DX�� Y��ǥ�� �ݴ��̴�.
		mousePosition.y = WIN_DEFAULT_HEIGHT - (float)GET_Y_LPARAM(lParam) * WIN_DEFAULT_HEIGHT / gWinHeight;
		//cout << "X : " << mousePosition.x << ", Y : " << mousePosition.y << '\n';

		//��Ŭ���� ����Ŭ���� ����.
		if (message == WM_LBUTTONDBLCLK)
			isDblClk = true;
		else
			isDblClk = false;
	}
}
