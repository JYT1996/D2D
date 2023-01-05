#include "stdafx.h"
#include "Program.h"


Program::Program()
{
	//����ڰ� ������â�� ũ�⸦ ��� �������� �𸣱� ������ -1 ~ 1�� ����ȭ�� �س��´�.
	//�׷��� �ʱ� ȭ���� ��ȯ�� �Ͼ�� ���� ���¿�����, ������ ������ -1 ~ 1�� ���ؼ� ���� �Ѱܾ��Ѵ�. 
	//���� -1, ������ 1, �Ʒ� -1, �� 1. windowAPI�� �ٸ���.
	
	//vertex
	{
		vertices.assign(3, VertexColor());
		vertices[0].position = {- 0.5f, -0.5f};
		vertices[0].color = { 1.0f, 0.0f, 0.0f, 1.0f };
		vertices[1].position = { -0.5f, 0.5f };
		vertices[1].color = { 1.0f, 0.0f, 0.0f, 1.0f };
		vertices[2].position = { 0.5f, -0.5f };
		vertices[2].color = { 1.0f, 0.0f, 0.0f, 1.0f };
	}

	//vertexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	
		desc.ByteWidth = sizeof(VertexColor) * (UINT)vertices.size();
		//Usage�� ���´� 4������ �ִ�.
		//�����ϰ� ��ȯ�� �ʿ���� �ڿ��� ��� IMMUTABLE. GPU�� ������ ���� ���� �ִ� ��(�б� ����). const ���� ���
		//DEFAULT�� GPU���� ������ �а� ������ �����ϴ�.
		//DYNAMIC GPU�� ������ �б⵵ �ϴµ�, CPU���� map�� ���ؼ� �����͸� ������ �ϱ⵵ �Ѵ�. CPU���� ���� �����ؼ� GPU�� ���� �� ����Ѵ�.
		//STAGING GPU�޸𸮿��� CPU�޸𸮷� ���縦 ����ϴ� ���̴�.
		desc.Usage = D3D11_USAGE_IMMUTABLE;	

		//GPU�� ���ϴ� ���������� �ܰ迡 ������ �־��ش�. vertexBuffer�� view�� �ʿ���� ������ enum�� ���� �����Ѵ�.
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		//CPU�� ���� ���� UINT CPUAccessFlags; ���� ���뵵�� �б��������� �س��� ������ ������ �ʿ����.

		//������ ������ ������ �ִ� ���� �ּҸ� �Ѱ��ֱ� ���� subData�� ������ �Ѵ�.		
		D3D11_SUBRESOURCE_DATA subData;
		ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
		subData.pSysMem = vertices.data();

		HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &vertexBuffer);
		CHECK(hr);
	}

	//inputLayoutDesc
	{
		//CPU�� GPU�� ������� �ȴ�.
		D3D11_INPUT_ELEMENT_DESC layoutDesc[]
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};	//���� ������ 2����� layoutDesc�� 2���� �ʿ��ϴ�. �迭�� ���ؼ� �ΰ� desc�� ���ļ� �����Ѵ�.
	}
}

Program::~Program()
{

}

void Program::Update()	//���� ������ �޽����� ������ �ϴ� ��.
{
	
}

void Program::Render()	//ȭ�鿡 ��µǰ� �޽����� ������ ��.
{
	
}
