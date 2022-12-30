#pragma once
//Popup console
#ifdef _DEBUG
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#endif

#include "targetver.h"
// 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#define WIN32_LEAN_AND_MEAN

// Windows 헤더 파일
#include <windows.h>
#include <windowsx.h>

// C 런타임 헤더 파일입니다.
#include <cassert>

// C++ 런타임 헤더 파일입니다.
#include <string>
#include <chrono>
#include <iostream>

using namespace std;

//DirectX D3D11
#include <d3d11.h>
#include <d3dcompiler.h>
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
using namespace DirectX;

//DirectXTK
#include "_Libraries/DirectXTK/SimpleMath.inl"
using namespace SimpleMath;

//Meacros
#define WIN_DEFAULT_WIDTH 1280.0f
#define WIN_DEFAULT_HEIGHT 720.0f

#define WIN_CENTER_X ( gWinWidth / 2 )
#define WIN_CENTER_Y ( gWinHeight / 2 )
#define WIN_CENTER ( Vector2 ( WIN_CENTER_X, WIN_CENTER_Y ))

#define SAFE_DELETE(p) { if (p) { delete(p); p = nullptr; } }
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[](p); p = nullptr; } }

#define DECLARE_SINGLETON(CLASS_NAME)							\
private:														\
CLASS_NAME();													\
~CLASS_NAME();													\
public:															\
CLASS_NAME(const CLASS_NAME& other) = delete;					\
CLASS_NAME& operator=(const CLASS_NAME& other) = delete;		\
CLASS_NAME(const CLASS_NAME&& other) = delete;					\
CLASS_NAME& operator=(const CLASS_NAME&& other) = delete;		\
public:															\
static CLASS_NAME* Get()										\
{																\
	static CLASS_NAME instance;									\
	return &instance;											\
}

//ExternGlobal
extern HWND gHandle;
extern HDC gHDC;
extern float gWinWidth;
extern float gWinHeight;

//Headers
#include "Systems/Input.h"
#include "Systems/Time.h"

//GetSingletonInstance
#define INPUT Input::Get()
#define TIME Time::Get()