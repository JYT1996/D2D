#include "stdafx.h"
#include "Scene4_Texture.h"

void Scene4::Init()
{
	rect1 = make_unique<TextureRect>(WIN_CENTER, Vector2(200, 200), 0.0f, L"_Textures/bk.bmp");
	rect2 = make_unique<TextureRect>(*rect1);

	RTT = make_unique<RenderTexture>();
	RTT->Initialize();

	renderingTexture = make_unique<TextureRect>(WIN_CENTER, WIN_CENTER * 2, 0.0f);
	renderingTexture->GetTexture()->SetSRV(RTT->GetSRV());	
}

void Scene4::Destroy()
{	
	renderingTexture.reset();

	RTT.reset();

	rect2.reset();
	rect1.reset();
}

void Scene4::Update()
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
		rect1->GetWorld()->Rotate(-200.0f);
	if (INPUT->Press(VK_RIGHT))
		rect1->GetWorld()->Rotate(200.0f);

	if (INPUT->Press(VK_LBUTTON) && rect1->GetCollider()->Intersect(INPUT->GetMousePosition()))
		rect1->GetWorld()->SetPosition(INPUT->GetMousePosition());

	rect1->Update();
	rect2->Update();

	renderingTexture->Update();

	if (INPUT->Down(VK_F11))
		RTT->SaveTexture(L"_ScreenShots/ScreenShot.bmp");
}

void Scene4::PreRender()
{
	RTT->RenderToTexture();
	{
		rect1->Render();
		rect2->Render();
	}	
}

void Scene4::Render()
{
	renderingTexture->Render();
}
