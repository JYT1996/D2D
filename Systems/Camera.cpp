#include "stdafx.h"
#include "Systems/Camera.h"

Camera::Camera()
{
	VPBuffer = make_unique<ViewProjectionBuffer>();

	eye = { position.x, position.y, 0 };
	at = { position.x, position.y, 1 };
	view = XMMatrixLookAtLH(eye, at, up);
	projection = XMMatrixOrthographicOffCenterLH(0, WIN_DEFAULT_WIDTH, 0, WIN_DEFAULT_HEIGHT, 0, 1);

	VPBuffer->SetView(view);
	VPBuffer->SetProjection(projection);
}

Camera::~Camera(){}

void Camera::Update()
{
	if (INPUT->Press(VK_LSHIFT) && INPUT->Press('I'))
		Move(Vector2(0, speed));
	if (INPUT->Press(VK_LSHIFT) && INPUT->Press('K'))
		Move(Vector2(0, -speed));
	if (INPUT->Press(VK_LSHIFT) && INPUT->Press('J'))
		Move(Vector2(-speed, 0));
	if (INPUT->Press(VK_LSHIFT) && INPUT->Press('L'))
		Move(Vector2(speed, 0));
}

void Camera::Render()
{
	VPBuffer->SetVSBuffer(1);
}

void Camera::UpdateView()
{
	eye = { position.x, position.y, 0 };
	at = { position.x, position.y, 1 };
	view = XMMatrixLookAtLH(eye, at, up);

	VPBuffer->SetView(view);
}

void Camera::SetPosition(const Vector2& position)
{
	this->position = position;

	UpdateView();
}

void Camera::Move(const Vector2& position)
{
	this->position += position * TIME->GetDeltaTime();

	UpdateView();
}
