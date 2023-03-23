#include "stdafx.h"
#include "Systems/Camera.h"

Camera::Camera()
{
	VPBuffer = make_unique<ViewProjectionBuffer>();

	eye = { position.x, position.y, 0 };
	at = { position.x, position.y, 1 };
	view = XMMatrixLookAtLH(eye, at, up);
	projection = XMMatrixOrthographicOffCenterLH(LB.x, RT.x, LB.y, RT.y, 0, 1);

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

	if (INPUT->Press(VK_LSHIFT) && INPUT->Press('U'))
		ZoomIn();
	if (INPUT->Press(VK_LSHIFT) && INPUT->Press('O'))
		ZoomOut();

	if (INPUT->Down(VK_F8))
		InitZoom();
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

void Camera::UpdateProj()
{
	projection = XMMatrixOrthographicOffCenterLH(LB.x, RT.x, LB.y, RT.y, 0, 1);

	VPBuffer->SetProjection(projection);
}

void Camera::SetPosition(const Vector2& position)
{
	this->position = position;

	if (bEdge)
	{
		if (this->position.x < minEdge.x)
			this->position.x = minEdge.x;
		else if (this->position.x + WIN_DEFAULT_WIDTH > maxEdge.x)
			this->position.x = maxEdge.x - WIN_DEFAULT_WIDTH;

		if (this->position.y < minEdge.y)
			this->position.y = minEdge.y;
		else if (this->position.y + WIN_DEFAULT_HEIGHT > maxEdge.y)
			this->position.y = maxEdge.y - WIN_DEFAULT_HEIGHT;
	}

	UpdateView();
}

void Camera::Move(const Vector2& position)
{
	this->position += position * TIME->GetDeltaTime();

	UpdateView();
}

Vector2 Camera::UnProject(const Vector2& source)
{
	Vector2 output;
	output = (source * 2.0f / Vector2(WIN_DEFAULT_WIDTH, WIN_DEFAULT_HEIGHT)) - Vector2(1, 1);

	Matrix VP = view * projection;
	VP = VP.Invert();

	return XMVector2TransformCoord(output, VP);
}

void Camera::ZoomIn()
{
	if (LB.y + zoomSpeed * TIME->GetDeltaTime() >= RT.y - zoomSpeed * TIME->GetDeltaTime())
		return;

	LB.x += zoomSpeed * widthRatio * TIME->GetDeltaTime();
	LB.y += zoomSpeed * TIME->GetDeltaTime();
	RT.x -= zoomSpeed * widthRatio * TIME->GetDeltaTime();
	RT.y -= zoomSpeed * TIME->GetDeltaTime();
	

	UpdateProj();
}

void Camera::ZoomOut()
{
	LB.x -= zoomSpeed * widthRatio * TIME->GetDeltaTime();
	LB.y -= zoomSpeed * TIME->GetDeltaTime();
	RT.x += zoomSpeed * widthRatio * TIME->GetDeltaTime();
	RT.y += zoomSpeed * TIME->GetDeltaTime();

	UpdateProj();
}

void Camera::InitZoom()
{
	LB = { 0,0 };
	RT = { gWinWidth, gWinHeight };

	UpdateProj();
}
