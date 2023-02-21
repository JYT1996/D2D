#pragma once

class Gui
{
	DECLARE_SINGLETON(Gui);

public:
	LRESULT MsgProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	void Resize();

	void PrintFrame();

	void Update();
	void Render();
};
