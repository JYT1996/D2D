#include "stdafx.h"
#include "Program.h"


Program::Program()
{
	//����ڰ� ������â�� ũ�⸦ ��� �������� �𸣱� ������ -1 ~ 1�� ����ȭ�� �س��´�.
	//�׷��� �ʱ� ȭ���� ��ȯ�� �Ͼ�� ���� ���¿�����, ������ ������ -1 ~ 1�� ���ؼ� ���� �Ѱܾ��Ѵ�. 
	//���� -1, ������ 1, �Ʒ� -1, �� 1. windowAPI�� �ٸ���.
	
	//vertex
	{
		vertices.assign(4, VertexColor());

		vertices[0].position = { -0.5f, -0.5f };
		vertices[0].color = { 1.0f, 0.0f, 0.0f, 1.0f };
		vertices[1].position = { -0.5f, 0.5f };
		vertices[1].color = { 1.0f, 0.0f, 0.0f, 1.0f };
		vertices[2].position = { 0.5f, -0.5f };
		vertices[2].color = { 1.0f, 0.0f, 0.0f, 1.0f };	
		vertices[3].position = { 0.5f, 0.5f };
		vertices[3].color = { 1.0f, 0.0f, 0.0f, 1.0f };
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


	//indexData
	{
		indices = { 0, 1, 2, 2, 1, 3 };
	}

	//indexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.ByteWidth = sizeof(UINT) * (UINT)indices.size();

		//�ּҸ� �Ѱ��ֱ� ���� ���굥����.
		D3D11_SUBRESOURCE_DATA subData;
		ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
		subData.pSysMem = indices.data();

		HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &indexBuffer);
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

	//CreateWorldViewProjection
	{
		Matrix S, R, T;

		//S._11 = 100;
		//S._22 = 100;
		
		//30���� �������� �ٲ㼭 �־��ش�.
		//R._11 = cosf(XMConvertToRadians(-30.0f));
		//R._12 = sinf(XMConvertToRadians(-30.0f));
		//R._21 = -sinf(XMConvertToRadians(-30.0f));
		//R._22 = cosf(XMConvertToRadians(-30.0f));
		
		//T._41 = 100;
		//T._42 = 100;

		S = XMMatrixScaling(50, 100, 1);
		R = XMMatrixRotationZ(XMConvertToRadians(-30.0f));
		T = XMMatrixTranslation(100, 100, 0);

		world = S * R * T;
		//LH�޼���ǥ��, RH ��������ǥ��. ���̴� z�� ����.
		//ī�޶��� ��ġ, ī�޶��� ����(����), ����
		//2D�� ���̴� ������ �ʿ�� ����.
		view = XMMatrixLookAtLH(Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(0, 1, 0));
		//DX�� �޼���ǥ. 
		projection = XMMatrixOrthographicLH(gWinWidth, gWinHeight, 0, 1);
	}

	//ConstantBuffer (�뵵�� ��Ȯ���� ���� ������ ���� ����)
	{		
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));

		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.ByteWidth = sizeof(TransformData);
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		
		HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, &gpuBuffer);
		CHECK(hr);
	}
}

Program::~Program()
{

}

void Program::Update()	//���� ������ �޽����� ������ �ϴ� ��.
{
	//GPU�� �ھ ���� ���÷� ������ �� ���ɼ��� �ִ�.
	//�ٸ� �ھ ������� �� cpu�� �����ϸ� �ȵǱ� ������ cpu�� ������ ���� gpu�� ���������� �ϰ��� ���� �־��ش�.
	//���� ���������� �������ش�. map �������� ���ϰ� ����, unmap ������ ���� Ǯ���ش�.
	//CPU������ world view projection�� ��켱 ����̴�. GPU�� ���켱 ����̴�. GPU�� ���� �־��ֱ� ���ؼ��� ��ġ��ķ� ���� ���� �־���� �Ѵ�.
	cpuBuffer.world = XMMatrixTranspose(world);
	cpuBuffer.view = XMMatrixTranspose(view);
	cpuBuffer.projection = XMMatrixTranspose(projection);

	D3D11_MAPPED_SUBRESOURCE mappedSubResource;
	//��� ���������� �� ���ΰ�. gpuBuffer, ����ϰ� cpu�� ���� �����ϰ� ���� ���ΰ�?
	//�װ��� �����ϱ� ���� �ּ�.
	DC->Map
	(
		gpuBuffer.Get(),
		0,
		D3D11_MAP_WRITE_DISCARD,	//��� �� ���
		0,
		&mappedSubResource
	);

	memcpy(mappedSubResource.pData, &cpuBuffer, sizeof(TransformData));

	DC->Unmap(gpuBuffer.Get(), 0);
}

void Program::Render()	//ȭ�鿡 ��µǰ� �޽����� ������ ��.
{
	//Strides ����
	UINT stride = sizeof(VertexColor);
	UINT offset = 0;
	
	//IA
	DC->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	DC->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	DC->IASetInputLayout(inputLayout.Get());
	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	//VS Constant Buffer
	DC->VSSetConstantBuffers(0, 1, gpuBuffer.GetAddressOf());

	//VS
	DC->VSSetShader(vertexShader.Get(), nullptr, 0);

	//PS
	DC->PSSetShader(pixelShader.Get(), nullptr, 0);

	//���������� ������ ���� �Է�������, ������ �׸���ȴ�.
	//�׸� ���� Draw�Լ��� ����Ѵ�. �Ű������� ������ ������ ������ �־��ش�.
	DC->DrawIndexed((UINT)indices.size(), 0, 0);
}
