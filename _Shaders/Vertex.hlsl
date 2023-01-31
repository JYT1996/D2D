//Vertex.hlsl�� ������۷� color���� �Ѱ� �� ���̱� ������ vertexBuffer���� �޾ƿ��� color�� �����Ѵ�.
struct VertexInput
{
    float4 position : POSITION0;
};
//���� �־��� ������� ���̴����� �޾���� �Ѵ�.
cbuffer World : register(b0)
{
    matrix _world;    
}

cbuffer ViewProjection : register(b1)
{
    matrix _view;
    matrix _proj;
}

struct PixelInput
{
    float4 position : SV_Position0;
};

//�������� VS�� ��Ƽ� �������� ���̴�.
PixelInput VS(VertexInput input)
{
    PixelInput output;
	
    output.position = mul(input.position, _world);
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _proj);
    
    return output;	
}
//������ۿ��� ���� �޾ƿ��� ���� register������ ���ش�.
cbuffer ColorBuffer : register(b0)
{
    float4 _color;
}

//�������� PS�� ��Ƽ� �������� ���̴�.
float4 PS(PixelInput input) : SV_Target
{
    return _color;
}