#include "stdafx.h"
#include "Program.h"


Program::Program()
{
	//사용자가 윈도우창의 크기를 어떻게 설정할지 모르기 때문에 -1 ~ 1로 정규화를 해놓는다.
	//그래서 초기 화면의 변환이 일어나지 않은 상태에서는, 정점의 정보를 -1 ~ 1를 통해서 값을 넘겨야한다. 
	//왼쪽 -1, 오른쪽 1, 아래 -1, 위 1. windowAPI랑 다르다.
	
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
		//Usage의 형태는 4가지가 있다.
		//생성하고 변환이 필요없는 자원일 경우 IMMUTABLE. GPU가 정보를 읽을 수만 있는 것(읽기 전용). const 같은 기능
		//DEFAULT는 GPU에서 정보를 읽고 수정도 가능하다.
		//DYNAMIC GPU가 정보를 읽기도 하는데, CPU에서 map을 통해서 데이터를 수정을 하기도 한다. CPU에서 값을 변경해서 GPU에 보낼 때 사용한다.
		//STAGING GPU메모리에서 CPU메모리로 복사를 허용하는 것이다.
		desc.Usage = D3D11_USAGE_IMMUTABLE;	

		//GPU의 원하는 파이프라인 단계에 정보를 넣어준다. vertexBuffer은 view가 필요없기 때문에 enum이 따로 존재한다.
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		//CPU의 접근 권한 UINT CPUAccessFlags; 현재 사용용도를 읽기전용으로 해놨기 때문에 권한이 필요없다.

		//정점의 정보를 가지고 있는 곳의 주소를 넘겨주기 위해 subData를 만들어야 한다.		
		D3D11_SUBRESOURCE_DATA subData;
		ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
		subData.pSysMem = vertices.data();

		HRESULT hr = DEVICE->CreateBuffer(&desc, &subData, &vertexBuffer);
		CHECK(hr);
	}

	//inputLayoutDesc
	{
		//CPU와 GPU의 연결고리가 된다.
		D3D11_INPUT_ELEMENT_DESC layoutDesc[]
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};	//정점 정보가 2개라면 layoutDesc은 2개가 필요하다. 배열을 통해서 두개 desc를 합쳐서 관리한다.
	}
}

Program::~Program()
{

}

void Program::Update()	//게임 로직의 메시지를 보내게 하는 것.
{
	
}

void Program::Render()	//화면에 출력되게 메시지를 보내는 것.
{
	
}
