#include "stdafx.h"
#include "Program.h"


Program::Program()
{
	//vertex
	{
		vertices.assign(4, VertexTexture());

		/*vertices[0].position = { -0.5f, -0.5f };
		vertices[0].color = { 1.0f, 0.0f, 0.0f, 1.0f };
		vertices[1].position = { -0.5f, 0.5f };
		vertices[1].color = { 1.0f, 0.0f, 0.0f, 1.0f };
		vertices[2].position = { 0.5f, -0.5f };
		vertices[2].color = { 1.0f, 0.0f, 0.0f, 1.0f };	
		vertices[3].position = { 0.5f, 0.5f };
		vertices[3].color = { 1.0f, 0.0f, 0.0f, 1.0f };*/

		vertices[0].position = { -0.5f, -0.5f };
		vertices[0].uv = { 0.0f , 1.0f };
		vertices[1].position = { -0.5f, 0.5f };
		vertices[1].uv = { 0.0f, 0.0f };
		vertices[2].position = { 0.5f, -0.5f };
		vertices[2].uv = { 1.0f, 1.0f };
		vertices[3].position = { 0.5f, 0.5f };
		vertices[3].uv = { 1.0f, 0.0f };
	}

	//vertexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	
		desc.ByteWidth = sizeof(VertexTexture) * (UINT)vertices.size();
		desc.Usage = D3D11_USAGE_IMMUTABLE;	

		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subData;
		ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
		subData.pSysMem = vertices.data();

		HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &vertexBuffer);
		CHECK(hr);
	}
	
	//vertexShader
	{
		HRESULT hr = D3DCompileFromFile
		(
			//L"_Shaders/Color.hlsl",
			L"_Shaders/Texture.hlsl",
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
		{
			/*{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},*/
			{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

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
	
	//pixerShader
	{
		HRESULT hr = D3DCompileFromFile
		(
			//L"_Shaders/Color.hlsl",
			L"_Shaders/Texture.hlsl",
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
		
		//R._11 = cosf(XMConvertToRadians(-30.0f));
		//R._12 = sinf(XMConvertToRadians(-30.0f));
		//R._21 = -sinf(XMConvertToRadians(-30.0f));
		//R._22 = cosf(XMConvertToRadians(-30.0f));
		
		//T._41 = 100;
		//T._42 = 100;

		S = XMMatrixScaling(500, 500, 1);
		R = XMMatrixRotationZ(XMConvertToRadians(0.0f));
		T = XMMatrixTranslation(100, 100, 0);

		world = S * R * T;
		view = XMMatrixLookAtLH(Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(0, 1, 0));
		projection = XMMatrixOrthographicLH(WIN_DEFAULT_WIDTH, WIN_DEFAULT_HEIGHT, 0, 1);
	}

	//ConstantBuffer (용도가 정확하지 않은 정보를 넣은 버퍼)
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

	//CreateRasterizerState
	{
		D3D11_RASTERIZER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
		desc.FillMode = D3D11_FILL_SOLID;

		desc.CullMode = D3D11_CULL_BACK;
		
		desc.FrontCounterClockwise = false;	

		HRESULT hr = DEVICE->CreateRasterizerState(&desc, &RS);
		CHECK(hr);
	}

	//SRV
	{
		//이미지가 있는 경로를 적는다.
		wstring path = L"_Textures/bk.bmp";
		//이미지를 담을 공간을 만든다.
		ScratchImage image;
		//이미지를 불러온다.
		LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, nullptr, image);
		//메타데이터란 그림의 정보(픽셀의 형식, 픽셀의 갯수)
		HRESULT hr = CreateShaderResourceView
		(
			DEVICE.Get(),
			image.GetImages(),
			image.GetImageCount(),
			image.GetMetadata(),
			&SRV
		);
		CHECK(hr);
	}

	//CreateSamplerState
	{
		//값을 크게 바꾸지 않고 기본값을 사용할 것이라면 이렇게 사용해도 된다.
		CD3D11_DEFAULT def;
		CD3D11_SAMPLER_DESC desc(def);
		//ZeroMemory(&desc, sizeof(CD3D11_SAMPLER_DESC));
		
		//텍스처 필터링의 방식.
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		desc.MipLODBias = 0;
		desc.MaxAnisotropy = 1;
		desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		desc.BorderColor[0] = 1.0f;
		desc.BorderColor[1] = 1.0f;
		desc.BorderColor[2] = 1.0f;
		desc.BorderColor[3] = 1.0f;
		desc.MinLOD = -3.402823466e+38F; // -FLT_MAX
		desc.MaxLOD = 3.402823466e+38F; // FLT_MAX

		HRESULT hr = DEVICE->CreateSamplerState(&desc, &samplerState); //업캐스팅을 이용해서 사용한다.
		CHECK(hr);
	}
}

Program::~Program()
{

}

void Program::Update()	//게임 로직의 메시지를 보내게 하는 것.
{
	cpuBuffer.world = XMMatrixTranspose(world);
	cpuBuffer.view = XMMatrixTranspose(view);
	cpuBuffer.projection = XMMatrixTranspose(projection);

	D3D11_MAPPED_SUBRESOURCE mappedSubResource;
	DC->Map
	(
		gpuBuffer.Get(),
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&mappedSubResource
	);

	memcpy(mappedSubResource.pData, &cpuBuffer, sizeof(TransformData));

	DC->Unmap(gpuBuffer.Get(), 0);
}

void Program::Render()
{
	//Strides 보폭
	UINT stride = sizeof(VertexTexture);
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
	
	//RS
	DC->RSSetState(RS.Get());

	//PS
	DC->PSSetShader(pixelShader.Get(), nullptr, 0);
	DC->PSSetShaderResources(0, 1, SRV.GetAddressOf());
	DC->PSSetSamplers(0, 1, samplerState.GetAddressOf());

	DC->DrawIndexed((UINT)indices.size(), 0, 0);
}
