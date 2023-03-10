#include "stdafx.h"
#include "Scene7_ImGui.h"

Scene7::Scene7()
{
	Path::GetFiles(paths, L"_Textures/", L"*.*", true);

	Path::CreateFolders(L"Directory/Sub1/Sub1_1");
	Path::CreateFolders(L"Directory/Sub1/Sub1_2");
	Path::CreateFolders(L"Directory/Sub2/Sub2_1");
}

void Scene7::Init()
{
	cout << '\n';
	for (const auto& path : paths)
	{
		wstring str = Path::GetFileNameWithoutExtension(path);
		wcout << str << '\n';
	}
}

void Scene7::Destroy()
{
	trVec.clear();
}

void Scene7::Update()
{
	if (INPUT->Down(VK_SPACE))
		trVec.push_back(make_shared<TextureRect>(INPUT->GetMousePosition(), Vector2(300, 300), 0.0f));

	for (const auto& tr : trVec)
		tr->Update();
}

void Scene7::PreRender()
{

}

void Scene7::Render()
{ 
	for (const auto& tr : trVec)
		tr->Render();
}

void Scene7::PostRender()
{
	IMGUI->TextureRectGUIS(trVec, "TextureRects");
}
