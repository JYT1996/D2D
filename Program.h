#pragma once

struct VertexColor
{
	Vector2 position;
	Color color;	//simplemath에 들어있는 클래스.
	//색을 정규화해서 나타내면 좋은 이유. 현재 색을 8bit로 표현하고 있는데, 
	//나중에 더 많은 비트를 통해서 표현하려 할 때 코드를 수정해야하는 상황이 올 수 있다.
	//하지만 정규화를 해놓으면 같은 비율로 색을 표현하기 때문에 코드를 수정하지 않을 수 있다.
};

class Program
{
public:
	Program();
	~Program();

public:
	void Update();
	void Render();

private:
	vector<VertexColor> vertices;
	//정보를 잠시 저장했다가 넘기는 것이기 때문에 buffer를 이용한다.
	ComPtr<ID3D11Buffer> vertexBuffer;		//CreateBuffer는 이중포인터로 값을 주기 때문에 그것을 위한 ComPtr이다.

	//쉐이더를 작성할 것인데, HLSL를 사용해서 코딩할 것이다.

	ComPtr<ID3D11InputLayout> inputLayout;	//정점의 정보를 쉐이더에 넘길 때 레이아웃도 넘겨서 확인을 해야한다.
};