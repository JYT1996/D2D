#include "stdafx.h"
#include "Program.h"


Program::Program()
{
	VPBuffer = make_unique<ViewProjectiondBuffer>();
	worldBuffer = make_unique<WorldBuffer>();
	rect = make_unique<ColorRect>();
	

	
	SetGlobalBuffer();	
}

Program::~Program()
{

}

void Program::SetGlobalBuffer()
{
	view = XMMatrixLookAtLH(Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(0, 1, 0));
	projection = XMMatrixOrthographicOffCenterLH(0, WIN_DEFAULT_WIDTH, 0, WIN_DEFAULT_HEIGHT, 0, 1);
}

void Program::Update()	//���� ������ �޽����� ������ �ϴ� ��.
{
	worldBuffer->SetWorld(world);
	VPBuffer->SetView(view);
	VPBuffer->SetProjection(projection);
}

void Program::Render()
{
	worldBuffer.get()->SetVSBuffer(0);
	VPBuffer.get()->SetVSBuffer(0);
	rect.get()->SetColorRect();	
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);	
	DC->DrawIndexed(rect.get()->GetIndicseSize(), 0, 0);
	//����
}
