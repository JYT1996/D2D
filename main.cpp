#include "stdafx.h"
#include "Systems/Window.h"

//전역변수를 선언해서 다른곳에서 사용할 수 있게 한다.
HWND gHandle = nullptr;
HDC gHDC = nullptr;
float gWinWidth = WIN_DEFAULT_WIDTH;
float gWinHeight = WIN_DEFAULT_HEIGHT;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	WinDesc desc;
	desc.appName = L"WinAPI";
	desc.instance = hInstance;
	desc.handle = nullptr;
	desc.width = WIN_DEFAULT_WIDTH;
	desc.height = WIN_DEFAULT_HEIGHT;


	Window* window = new Window(desc);
	WPARAM wParam = window->Run();
	SAFE_DELETE(window);

	return (int)wParam;
}