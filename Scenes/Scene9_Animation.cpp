#include "stdafx.h"
#include "Scene9_Animation.h"

void Scene9::Init()
{
	Vector2 mapSize = Vector2(800 * 3.0f, 800 * 3.0f);
	background = make_unique<TextureRect>(mapSize / 2.0f, mapSize, 0.0f, L"_Textures/map.png");

	animRect = make_unique<AnimationRect>(Vector2(300, 300), Vector2(100, 100), 0.0f, L"_Textures/rockman.bmp");
	
	ScratchImage* image = animRect->GetTexture()->GetImage();

	animRect->AddAnimClip(make_shared<AnimationClip>(L"RunR", *image, 10, Vector2(0, 0), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height / 2)));
	animRect->AddAnimClip(make_shared<AnimationClip>(L"RunL", *image, 10, Vector2(0, (float)image->GetMetadata().height / 2.0f), Vector2((float)image->GetMetadata().width, (float)image->GetMetadata().height), true));
	animRect->SetAnimator(make_shared<Animator>(animRect->GetAnimClips()));
}

void Scene9::Destroy()
{
	
}

void Scene9::Update()
{
	background->Update();

	if (INPUT->Press('W'))
		animRect->GetWorld()->Move(Vector2(0, 500));
	if (INPUT->Press('S'))
		animRect->GetWorld()->Move(Vector2(0, -500));
	if (INPUT->Press('A'))
	{
		animRect->GetAnimator()->SetCurrentAnimClip(L"RunL");
		animRect->GetWorld()->Move(Vector2(-500, 0));
	}
	if (INPUT->Press('D'))
	{
		animRect->GetAnimator()->SetCurrentAnimClip(L"RunR");
		animRect->GetWorld()->Move(Vector2(500, 0));
	}

	animRect->Update();
}

void Scene9::PreRender()
{

}

void Scene9::Render()
{ 
	background->Render();
	animRect->Render();
}

void Scene9::PostRender()
{
	
}