#pragma once
//키를 받을 수 있는 최대 크기.
#define MAX_INPUT_KEY 256

class Input
{
	//매크로를 이용한 싱클톤. 생성자와 소멸자를 정의해야 한다.
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
	//키 배열에 마우스클릭도 들어가기 때문에 그걸 이용해 간격을 보고 더블클릭으로 인식할 수 있지만, 다르게 할 것이다.
	bool isDblClk = false;

	enum
	{
		KEY_INPUT_STATUS_NONE = 0,
		KEY_INPUT_STATUS_DOWN,
		KEY_INPUT_STATUS_UP,
		KEY_INPUT_STATUS_PRESS,
	};
};