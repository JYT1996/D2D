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
	ComPtr<ID3D11Buffer> vertexBuffer;		//COMI�� ���������ͷ� ���� �ֱ� ������ �װ��� ���� ComPtr�̴�.

	vector<UINT> indices;
	ComPtr<ID3D11Buffer> indexBuffer;
	//���̴��� �ۼ��� ���ε�, HLSL�� ����ؼ� �ڵ��� ���̴�.
	//�����Ϸ��� HLSL�� �ۼ��� ���� ������������ �ʴ´�. ����ڰ� ���� �������� �ϰԲ� ����ؾ� �Ѵ�.
	ComPtr<ID3DBlob> vsBlob;
	ComPtr<ID3D11VertexShader> vertexShader;

	ComPtr<ID3D11InputLayout> inputLayout;	//������ ������ ���̴��� �ѱ� �� ���̾ƿ��� �Ѱܼ� ������ Ȯ���� �ؾ��Ѵ�.

	ComPtr<ID3DBlob> psBlob;
	ComPtr<ID3D11PixelShader> pixelShader;
};