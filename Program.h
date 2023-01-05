#pragma once

struct VertexColor
{
	Vector2 position;
	Color color;	//simplemath�� ����ִ� Ŭ����.
	//���� ����ȭ�ؼ� ��Ÿ���� ���� ����. ���� ���� 8bit�� ǥ���ϰ� �ִµ�, 
	//���߿� �� ���� ��Ʈ�� ���ؼ� ǥ���Ϸ� �� �� �ڵ带 �����ؾ��ϴ� ��Ȳ�� �� �� �ִ�.
	//������ ����ȭ�� �س����� ���� ������ ���� ǥ���ϱ� ������ �ڵ带 �������� ���� �� �ִ�.
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
	//������ ��� �����ߴٰ� �ѱ�� ���̱� ������ buffer�� �̿��Ѵ�.
	ComPtr<ID3D11Buffer> vertexBuffer;		//CreateBuffer�� ���������ͷ� ���� �ֱ� ������ �װ��� ���� ComPtr�̴�.

	//���̴��� �ۼ��� ���ε�, HLSL�� ����ؼ� �ڵ��� ���̴�.

	ComPtr<ID3D11InputLayout> inputLayout;	//������ ������ ���̴��� �ѱ� �� ���̾ƿ��� �Ѱܼ� Ȯ���� �ؾ��Ѵ�.
};