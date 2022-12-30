#pragma once
//Ű�� ���� �� �ִ� �ִ� ũ��.
#define MAX_INPUT_KEY 256

class Input
{
	//��ũ�θ� �̿��� ��Ŭ��. �����ڿ� �Ҹ��ڸ� �����ؾ� �Ѵ�.
	DECLARE_SINGLETON(Input);

public:
	void Updata();

	void InputProc(UINT message, LPARAM lParam);

	bool Down(DWORD key) { return keyMap[key] == KEY_INPUT_STATUS_DOWN; }
	bool Up(DWORD key) { return keyMap[key] == KEY_INPUT_STATUS_UP; }
	bool Press(DWORD key) { return keyMap[key] == KEY_INPUT_STATUS_PRESS; }
	bool DblClk() { return isDblClk; }

	Vector2 GetMousePosition() { return mousePosition; }

private:
	Vector2 mousePosition;

	unsigned char keyState[MAX_INPUT_KEY] = { 0 };
	unsigned char keyOldState[MAX_INPUT_KEY] = { 0 };
	unsigned char keyMap[MAX_INPUT_KEY] = { 0 };
	//Ű �迭�� ���콺Ŭ���� ���� ������ �װ� �̿��� ������ ���� ����Ŭ������ �ν��� �� ������, �ٸ��� �� ���̴�.
	bool isDblClk = false;

	enum
	{
		KEY_INPUT_STATUS_NONE = 0,
		KEY_INPUT_STATUS_DOWN,
		KEY_INPUT_STATUS_UP,
		KEY_INPUT_STATUS_PRESS,
	};
};