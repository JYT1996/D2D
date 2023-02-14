#include "stdafx.h"
#include "Scene5_TextureInverse.h"

void Scene5::Init()
{
	rect1 = make_unique<ColorRect>(Vector2(200, 200), Vector2(100.0f, 100.0f), 0.0f, CYAN);
	rect2 = make_unique<ColorRect>(Vector2(400, 400), Vector2(100.0f, 100.0f), 0.0f);

	RTT = make_unique<RenderTexture>();
	RTT->Initialize();

	//renderingTexture = make_unique<TextureRect>(WIN_CENTER, WIN_CENTER * 2, 0);
	//renderingTexture->GetTexture()->SetSRV(RTT->GetSRV());	
	//renderingTexture->SetShader(L"_Shaders/VertexTextureInverse.hlsl");
	//renderingTexture->AddComponent(make_shared<SelectionComponent>());

	test.resize(1);
	for (auto& texture : test)
	{
		texture = make_unique<TextureRect>(WIN_CENTER, WIN_CENTER * 2, 0);
		texture->GetTexture()->SetSRV(RTT->GetSRV());
		texture->SetShader(L"_Shaders/VertexTextureInverse.hlsl");
		texture->AddComponent(make_shared<SelectionComponent>());
	}
}

void Scene5::Destroy()
{	
	//renderingTexture.reset();
	for (auto& texture : test)
		texture.reset();

	RTT.reset();

	rect2.reset();
	rect1.reset();
}

void Scene5::Update()
{
	if (INPUT->Press('W'))
		rect1->GetWorld()->Move(Vector2(0, 300));
	if (INPUT->Press('S'))
		rect1->GetWorld()->Move(Vector2(0, -300));
	if (INPUT->Press('A'))
		rect1->GetWorld()->Move(Vector2(-300, 0));
	if (INPUT->Press('D'))
		rect1->GetWorld()->Move(Vector2(300, 0));
	if (INPUT->Press(VK_DOWN))
		rect1->GetWorld()->Scale(Vector2(-150, -150));
	if (INPUT->Press(VK_UP))
		rect1->GetWorld()->Scale(Vector2(150, 150));

	if (INPUT->Press(VK_LEFT))
		rect1->GetWorld()->Rotat(-200.0f);
	if (INPUT->Press(VK_RIGHT))
		rect1->GetWorld()->Rotat(200.0f);

	if (rect1->GetCollider()->intersect(rect2->GetCollider()))
		rect2->GetColorComp()->SetColor(GREEN);
	else
		rect2->GetColorComp()->SetColor(RED);

	if (INPUT->Press(VK_LBUTTON) && rect1->GetCollider()->intersect(INPUT->GetMousePosition()))
		rect1->GetWorld()->SetPosition(INPUT->GetMousePosition());

	if (INPUT->Down('2'))
	{
		test.resize(2);
		test.push_back(make_unique<TextureRect>(WIN_CENTER / 2, WIN_CENTER, 0));
		

	}


	rect1->Update();
	rect2->Update();

	//renderingTexture->Update();

	for (auto& texture : test)
	{
		texture->Update();
	}

	if (INPUT->Down(VK_F11))
		RTT->SaveTexture(L"_ScreenShots/ScreenShot.bmp");
}

void Scene5::PreRender()
{
	RTT->RenderToTexture();
	{
		rect1->Render();
		rect2->Render();
	}	
}

void Scene5::Render()
{
	for (auto& texture : test)
	{
		texture->Render();
	}
	//renderingTexture->Render();
}
