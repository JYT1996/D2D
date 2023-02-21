#include "stdafx.h"
#include "Scene7_ImGui.h"

Scene7::Scene7()
{
	//*.* '*'은 어떤 확장자를 가져오고 이름도 가져올 수 있다.
	Path::GetFiles(paths, L"_Textures/", L"*.*", true);

	Path::CreateFolders(L"Directory/Sub1/Sub1_1");
	Path::CreateFolders(L"Directory/Sub1/Sub1_2");
	Path::CreateFolders(L"Directory/Sub1/Sub2_1");
}

void Scene7::Init()
{
	cout << '\n';
	for (const auto& path : paths)
	{
		wstring str = Path::GetFileName(path);
		wcout << str << '\n';
	}
}

void Scene7::Destroy()
{	
	
}

void Scene7::Update()
{
	
}

void Scene7::PreRender()
{
	
}

void Scene7::Render()
{
}
