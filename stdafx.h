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
#include <vector>
#include <map>
#include <array>
using namespace std;

//DirectX D3D11
#include <d3d11.h>
#include <d3dcompiler.h>
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

//WRL
#include <wrl.h>
using namespace Microsoft;
using namespace WRL;

//DirectXTK
#include "_Libraries/DirectXTK/SimpleMath.h"
using namespace DirectX;
using namespace SimpleMath;

//DirectXTex
#include "_Libraries/DirectXTex/DirectXTex.h"
#ifdef _M_X64
	#ifdef _DEBUG
		#pragma comment(lib, "_Libraries/DirectXTex/x64/Debug/DirectXTex.lib")
	#elif NDEBUG
		#pragma comment(lib, "_Libraries/DirectXTex/x64/Release/DirectXTex.lib")
	#endif
#elif _M_IX86
	#ifdef _DEBUG
		#pragma comment(lib, "_Libraries/DirectXTex/Win32/Debug/DirectXTex.lib")
	#elif NDEBUG
		#pragma comment(lib, "_Libraries/DirectXTex/Win32/Release/DirectXTex.lib")
	#endif
#endif
//Meacros
#define WIN_DEFAULT_WIDTH 1280.0f
#define WIN_DEFAULT_HEIGHT 720.0f

#define WIN_CENTER_X ( gWinWidth / 2 )
#define WIN_CENTER_Y ( gWinHeight / 2 )
#define WIN_CENTER ( Vector2 ( WIN_CENTER_X, WIN_CENTER_Y ))

#define CHECK(hr) { assert(SUCCEEDED(hr)); }
#define SUPER __super

#define SAFE_DELETE(p) { if (p) { delete(p); p = nullptr; } }
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[](p); p = nullptr; } }
#define SAFE_RELEASE(p) { if (p) { p->Release(); p = nullptr; } }

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

//Singletons
#include "Systems/Input.h"
#include "Systems/Time.h"
#include "Systems/Graphics.h"

//GetSingletonInstance
#define INPUT Input::Get()
#define TIME Time::Get()
#define GRAPHICS Graphics::Get()
#define DEVICE GRAPHICS->GetDevice()
#define DC GRAPHICS->GetDC()

//ColorMacros
#define RED Color(1, 0, 0, 1)
#define GREEN Color(0, 1, 0, 1)
#define BLUE Color(0, 0, 1, 1)
#define YELLOW Color(1, 1, 0, 1)
#define MAGENTA Color(1, 0, 1, 1)
#define CYAN Color(0, 1, 1, 1)
#define WHITE Color(1, 1, 1, 1)
#define BLACK Color(0, 0, 0, 1)
 
//VectorMacros
#define RIGHT Vector2(1.0f, 0.0f)
#define UP Vector2(0.0f, 1.0f)

//Headers
#include "Renders/Resources/VertexType.h"
#include "Renders/IA/VertexBuffer.h"
#include "Renders/Shaders/IShader.h"
#include "Renders/Shaders/VertexShader.h"
#include "Renders/IA/IndexBuffer.h"
#include "Renders/IA/InputLayout.h"
#include "Renders//Shaders/PixelShader.h"
#include "Renders/Resources/ConstantBuffer.h"
#include "Renders//Resources/GlobalBuffer.h"

//Utilities
#include "Utilities/Collision.h"

//Components
#include "Component/Component.h"
#include "Component/WorldComponent.h"
#include "Component//ColorComponent.h"

//Object
#include "Objects/Object.h"
#include "Objects/Drawable.h"
#include "Objects/ColorRect.h"
#include "Objects/Line.h"
#include "Objects/Circle.h"
#include "Objects/FilledCircle.h"

//Scene
#include "Scenes/Scene.h"
