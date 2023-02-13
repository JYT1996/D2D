#include "stdafx.h"
#include "Window.h"
#include "Program.h"
unique_ptr<Program> Window::program = nullptr;
bool Window::isWindowCreated = false;

Window::Window(WinDesc initDesc)
{
	_desc = initDesc;
	WORD wHr = MyRegisterClass(_desc);
	assert(wHr != 0);

	_desc.handle = CreateWindowExW
	(
		WS_EX_APPWINDOW,
		_desc.appName.c_str(),
		_desc.appName.c_str(),
		WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		nullptr,
		(HMENU)nullptr,
		_desc.instance,
		nullptr
	);
	RECT rect = { 0, 0, (LONG)_desc.width, (LONG)_desc.height };
	UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)_desc.width) / 2;
	UINT centerY = (GetSystemMetrics(SM_CYSCREEN) - (UINT)_desc.height) / 2;

	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, 0);
	MoveWindow(_desc.handle, centerX, centerY, (int)_desc.width, (int)_desc.height, true);

	ShowWindow(_desc.handle, SW_SHOWNORMAL);
	UpdateWindow(_desc.handle);

	ShowCursor(true);

	isWindowCreated = true;
}

Window::~Window()
{
	DestroyWindow(_desc.handle);
	UnregisterClassW(_desc.appName.c_str(), _desc.instance);
}

ATOM Window::MyRegisterClass(WinDesc desc)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = desc.instance;
	wcex.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = desc.appName.c_str();
	wcex.hIconSm = wcex.hIcon;
	return RegisterClassExW(&wcex);
}

WPARAM Window::Run()
{
	MSG msg = { 0 };

	program = make_unique<Program>();
	program->Init();

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			INPUT->InputProc(msg.message, msg.lParam);

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			INPUT->Update();
			TIME->Update();
			program->Update();
			//다른 도화지에 그림을 그리는 것이다.
			program->PreRender();
			GRAPHICS->Begin();
			{
				program->Render();
				program->PostRender();
			}
			GRAPHICS->End();
		}
	}
	return msg.wParam;
}

LRESULT Window::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		gHandle = handle;
		break;
	case WM_SIZE:
		gWinWidth = LOWORD(lParam);
		gWinHeight = HIWORD(lParam);
		//cout << "X : " << gWinWidth << ", Y : " << gWinHeight << '\n';
		break;
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(handle, message, wParam, lParam);
}
