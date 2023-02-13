#include "stdafx.h"
#include "Scene4_Texture.h"

void Scene4::Init()
{
	rect1 = make_unique<TextureRect>(WIN_CENTER, Vector2(200.0f, 200.0f), 0.0f, L"_Textures/bk.bmp");
	rect2 = make_unique<TextureRect>(*rect1);
}

void Scene4::Destroy()
{	
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
		rect1->GetWorld()->Rotat(-200.0f);
	if (INPUT->Press(VK_RIGHT))
		rect1->GetWorld()->Rotat(200.0f);

	if (INPUT->Press(VK_LBUTTON) && rect1->GetCollider()->intersect(INPUT->GetMousePosition()))
		rect1->GetWorld()->SetPosition(INPUT->GetMousePosition());

	rect1->Update();
	rect2->Update();
}

void Scene4::Render()
{
	rect1->Render();
	rect2->Render();
}
