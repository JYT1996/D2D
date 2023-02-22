#include "stdafx.h"
#include "Gui.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Gui::Gui()
{
	//imgui를 초기화하는 과정
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui_ImplWin32_Init(gHandle);
	ImGui_ImplDX11_Init(DEVICE.Get(), DC.Get());
}

Gui::~Gui()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

LRESULT Gui::MsgProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	return ImGui_ImplWin32_WndProcHandler(handle, message, wParam, lParam);
}

void Gui::Resize()
{
	ImGui_ImplDX11_InvalidateDeviceObjects();
	ImGui_ImplDX11_CreateDeviceObjects();
}

void Gui::PrintFrame()
{
	bool temp = true;
	ImGui::SetNextWindowPos({ gWinWidth - 150, 0 });
	if (ImGui::Begin("FrameRate", &temp, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize));
	{
		//정수로 보는 것이 보기 좋아서 (int)로 형변환을 해주고 string한 것이다.
		string frameStr = "Frame Rate : " + to_string((int)ImGui::GetIO().Framerate);
		ImGui::TextColored(ImVec4(1, 1, 1, 1), frameStr.c_str());
	}
	ImGui::End();
}

void Gui::Update()
{
	ImGui_ImplWin32_NewFrame();
	ImGui_ImplDX11_NewFrame();
	ImGui::NewFrame();
}

void Gui::Render()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void Gui::TextureRectGUIS(vector<shared_ptr<class TextureRect>>& trVec, const char* name)
{
	if (trVec.size() <= 0) return;
	
	bool temp = true;
	if (ImGui::Begin(name, &temp))
	{		
		for (size_t i = 0; i < trVec.size(); ++i)
			trVec[i]->GUI(i);
	}
	ImGui::End();
}
