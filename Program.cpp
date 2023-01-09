#include "stdafx.h"
#include "Program.h"


Program::Program()
{
	//����ڰ� ������â�� ũ�⸦ ��� �������� �𸣱� ������ -1 ~ 1�� ����ȭ�� �س��´�.
	//�׷��� �ʱ� ȭ���� ��ȯ�� �Ͼ�� ���� ���¿�����, ������ ������ -1 ~ 1�� ���ؼ� ���� �Ѱܾ��Ѵ�. 
	//���� -1, ������ 1, �Ʒ� -1, �� 1. windowAPI�� �ٸ���.
	
	//vertex
	{
		vertices.assign(23, VertexColor());		
		//1��° ��
		vertices[0].position = { 0.0f, 0.7f };
		vertices[0].color = { 0.0f, 0.4f, 0.0f, 1.0f };
		vertices[1].position = { 0.1f, 0.4f };
		vertices[1].color = { 0.0f, 0.4f, 0.0f, 1.0f };
		vertices[2].position = { -0.1f, 0.4f };
		vertices[2].color = { 0.0f, 0.4f, 0.0f, 1.0f };
		//2��° ��
		vertices[3].position = { 0.0f, 0.55f };
		vertices[3].color = { 0.0f, 0.4f, 0.0f, 1.0f };
		vertices[4].position = { 0.17f, 0.1f };
		vertices[4].color = { 0.0f, 0.4f, 0.0f, 1.0f };
		vertices[5].position = { -0.17f, 0.1f };
		vertices[5].color = { 0.0f, 0.4f, 0.0f, 1.0f };
		//3��° ��
		vertices[6].position = { 0.0f, 0.35f };
		vertices[6].color = { 0.0f, 0.4f, 0.0f, 1.0f };
		vertices[7].position = { 0.25f, -0.2f };
		vertices[7].color = { 0.0f, 0.4f, 0.0f, 1.0f };
		vertices[8].position = { -0.25f, -0.2f };
		vertices[8].color = { 0.0f, 0.4f, 0.0f, 1.0f };
		//4��° ��
		vertices[9].position = { 0.0f, 0.0f };
		vertices[9].color = { 0.0f, 0.4f, 0.0f, 1.0f };
		vertices[10].position = { 0.3f, -0.65f };
		vertices[10].color = { 0.0f, 0.4f, 0.0f, 1.0f };
		vertices[11].position = { -0.3f, -0.65f };
		vertices[11].color = { 0.0f, 0.4f, 0.0f, 1.0f };
		//�������
		vertices[12].position = { -0.04f, -0.85f };
		vertices[12].color = {0.58f, 0.3f, 0.0f, 1.0f};
		vertices[13].position = { -0.04f, -0.65f };
		vertices[13].color = { 0.58f, 0.3f, 0.0f, 1.0f };
		vertices[14].position = { 0.04f, -0.85f };
		vertices[14].color = { 0.58f, 0.3f, 0.0f, 1.0f };
		vertices[15].position = { 0.04f, -0.65f };
		vertices[15].color = { 0.58f, 0.3f, 0.0f, 1.0f };
		//��
		vertices[16].position = { -0.04f, 0.7f };
		vertices[16].color = { 1.0f, 1.0f, 0.2f, 1.0f };
		vertices[17].position = { 0.04f, 0.7f };
		vertices[17].color = { 1.0f, 1.0f, 0.2f, 1.0f };
		vertices[18].position = { 0.0f, 0.65f };
		vertices[18].color = { 1.0f, 1.0f, 0.2f, 1.0f };

		vertices[19].position = { -0.03f, 0.6f };
		vertices[19].color = { 1.0f, 1.0f, 0.2f, 1.0f };
		vertices[20].position = { 0.0f, 0.75f };
		vertices[20].color = { 1.0f, 1.0f, 0.2f, 1.0f };
		vertices[21].position = { 0.03f, 0.6f };
		vertices[21].color = { 1.0f, 1.0f, 0.2f, 1.0f };
		vertices[22].position = { 0.0f, 0.65f };
		vertices[22].color = { 1.0f, 1.0f, 0.2f, 1.0f };

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

	
	//HLSL�� define�̳� include�� Ȱ���� �� �ִ�.
	//Binary Large Object, �������� �Ϸ�� ������ �ǹ��Ѵ�.
	//���̴��� ���� �������ϱ� ������ ���̴����� ������ ���� �� ���� �޽����� ���. 
	//vertexShader
	{
		HRESULT hr = D3DCompileFromFile
		(
			L"_Shaders/Color.hlsl",
			nullptr,
			nullptr,
			"VS",
			"vs_5_0",
			0,
			0,
			&vsBlob,
			nullptr
		);
		CHECK(hr);

		hr = DEVICE->CreateVertexShader
		(
			vsBlob->GetBufferPointer(),
			vsBlob->GetBufferSize(),
			nullptr,
			&vertexShader
		);
		CHECK(hr);
	}

	//inputLayout
	{
		//inputLayoutDesc
		D3D11_INPUT_ELEMENT_DESC layoutDesc[]
		//CPU�� GPU�� ������� �ȴ�.
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};	//���� ������ 2����� layoutDesc�� 2���� �ʿ��ϴ�. �迭�� ���ؼ� �ΰ� desc�� ���ļ� �����Ѵ�.

		//�������� �� �� �񱳸� �Ѵ�. �ø�ƽ�� �¾ƾ� ������ �ȴ�.
		HRESULT hr = DEVICE->CreateInputLayout
		(
			layoutDesc,
			2,
			vsBlob->GetBufferPointer(),
			vsBlob->GetBufferSize(),
			&inputLayout
		);
		CHECK(hr);
	}
	//RS�ܰ�� �˾Ƽ� �����ֱ� ������ ���̴��� �ʿ����� �ʴ�.
	
	//pixerShader
	{
		HRESULT hr = D3DCompileFromFile
		(
			L"_Shaders/Color.hlsl",
			nullptr,
			nullptr,
			"PS",
			"ps_5_0",
			0,
			0,
			&psBlob,
			nullptr
		);
		CHECK(hr);

		hr = DEVICE->CreatePixelShader
		(
			psBlob->GetBufferPointer(),
			psBlob->GetBufferSize(),
			nullptr,
			&pixelShader
		);
		CHECK(hr);
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
	//Strides ����
	UINT stride = sizeof(VertexColor);
	UINT offset = 0;
	
	//IA
	DC->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	DC->IASetInputLayout(inputLayout.Get());
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	//VS
	DC->VSSetShader(vertexShader.Get(), nullptr, 0);

	//PS
	DC->PSSetShader(pixelShader.Get(), nullptr, 0);

	//���������� ������ ���� �Է�������, ������ �׸���ȴ�.
	//�׸� ���� Draw�Լ��� ����Ѵ�. �Ű������� ������ ������ ������ �־��ش�.
	DC->Draw(12, 0);
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	DC->Draw(4, 12);
	DC->Draw(7, 16);
}
