#include "stdafx.h"
#include "Scene6_TextureEffect.h"

void Scene6::Init()
{
	rect1 = make_unique<ColorRect>(Vector2(200, 200), Vector2(100.0f, 100.0f), 0.0f, CYAN);
	rect2 = make_unique<ColorRect>(Vector2(400, 400), Vector2(100.0f, 100.0f), 0.0f);

	RTT = make_unique<RenderTexture>();
	RTT->Initialize();

	renderingTexture = make_unique<TextureRect>(WIN_CENTER, WIN_CENTER * 2, 0);
	renderingTexture->GetTexture()->SetSRV(RTT->GetSRV());	
	//renderingTexture->SetShader(L"_Shaders/VertexTextureInverse.hlsl");
	//renderingTexture->SetShader(L"_Shaders/Grayscale.hlsl");
	renderingTexture->SetShader(L"_Shaders/Vignette.hlsl");
	//renderingTexture->SetShader(L"_Shaders/Blur.hlsl");
	renderingTexture->AddComponent(make_shared<SelectionComponent>(1));
}

void Scene6::Destroy()
{	
	renderingTexture.reset();
	RTT.reset();

	rect2.reset();
	rect1.reset();
}

void Scene6::Update()
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

	rect1->Update();
	rect2->Update();

	renderingTexture->Update();

	if (INPUT->Down(VK_F11))
		RTT->SaveTexture(L"_ScreenShots/ScreenShot.bmp");
}

void Scene6::PreRender()
{
	RTT->RenderToTexture();
	{
		rect1->Render();
		rect2->Render();
	}	
}

void Scene6::Render()
{	
	renderingTexture->Render();
}
