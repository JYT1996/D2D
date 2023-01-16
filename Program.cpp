#include "stdafx.h"
#include "Program.h"


Program::Program()
{
	VPBuffer = make_unique<ViewProjectiondBuffer>();

	SetGlobalBuffer();

	rect = make_unique<ColorRect>();
}

Program::~Program()
{

}

void Program::SetGlobalBuffer()
{
	view = XMMatrixLookAtLH(Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(0, 1, 0));
	projection = XMMatrixOrthographicOffCenterLH(0, WIN_DEFAULT_WIDTH, 0, WIN_DEFAULT_HEIGHT, 0, 1);

	VPBuffer->SetView(view);
	VPBuffer->SetProjection(projection);

}

void Program::Update()	//게임 로직의 메시지를 보내게 하는 것.
{
	

	//rect 업데이트
}

void Program::Render()
{
	VPBuffer->SetVSBuffer(1);
	//렌더
}
