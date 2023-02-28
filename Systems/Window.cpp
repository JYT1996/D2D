#include "stdafx.h"
#include "Window.h"
#include "Program.h"

unique_ptr<Program> Window::program = nullptr;
bool Window::isWindowCreated = false;

Window::Window(WinDesc initDesc)
{
	desc = initDesc;

	WORD wHr = MyRegisterClass(desc);
	assert(wHr != 0);

	desc.handle = CreateWindowExW
	(
		WS_EX_APPWINDOW,
		desc.appName.c_str(),
		desc.appName.c_str(),
		WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		nullptr,
		(HMENU)nullptr,
		desc.instance,
		nullptr
	);

	RECT rect = { 0, 0, (LONG)desc.width, (LONG)desc.height };

	UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)desc.width) / 2;
	UINT centerY = (GetSystemMetrics(SM_CYSCREEN) - (UINT)desc.height) / 2;

	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, 0);

	MoveWindow(desc.handle, centerX, centerY, (int)desc.width, (int)desc.height, true);

	ShowWindow(desc.handle, SW_SHOWNORMAL);
	UpdateWindow(desc.handle);

	ShowCursor(true);
}

Window::~Window()
{
	DestroyWindow(desc.handle);
	UnregisterClassW(desc.appName.c_str(), desc.instance);
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

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			INPUT->Update();
			TIME->Update();

			IMGUI->Update();

			program->Update();
			
			program->PreRender();
			GRAPHICS->Begin();
			{
				program->Render();
				program->PostRender();
				IMGUI->Render();
			}
			GRAPHICS->End();
		}
	}

	return msg.wParam;
}

LRESULT Window::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (isWindowCreated)
	{
		INPUT->InputProc(message, lParam);
		if (IMGUI->MsgProc(handle, message, wParam, lParam))
			return true;
	}

	switch (message)
	{
	case WM_CREATE:
		isWindowCreated = true;
		gHandle = handle;
		break;
	case WM_SIZE:
		gWinWidth = (float)GET_X_LPARAM(lParam);
		gWinHeight = (float)GET_Y_LPARAM(lParam);
		GRAPHICS->Resize(gWinWidth, gWinHeight);
		//cout << "X : " << gWinWidth << ", Y : " << gWinHeight << '\n';
		break;
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);

		return 0;
	}

	return DefWindowProc(handle, message, wParam, lParam);
}
