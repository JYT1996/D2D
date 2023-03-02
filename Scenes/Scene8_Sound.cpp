#include "stdafx.h"
#include "Scene8_Sound.h"

void Scene8::Init()
{
	assert(SOUND->AddSound("0", L"_Sounds/war.mp3", true));
	//assert(SOUND->AddSound("0", L"_Sounds/play_fire.wav", false, true));	
}

void Scene8::Destroy()
{
	
}

void Scene8::Update()
{

}

void Scene8::PreRender()
{

}

void Scene8::Render()
{ 

}

void Scene8::PostRender()
{
	bool temp = true;
	if (ImGui::Begin("Sounds"), &temp)
	{
		SOUND->GUI("0");
		SOUND->GUI("1");
	}
	ImGui::End();
}