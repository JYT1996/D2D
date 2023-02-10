struct VertexInput
{
	float4 position : POSITION0;
	float2 uv : TEXCOORD0;
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
    float2 uv : TEXCOORD0;
};

//�������� VS�� ��Ƽ� �������� ���̴�.
PixelInput VS(VertexInput input)
{
    PixelInput output;
	
    output.position = mul(input.position, _world);
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _proj);
    
    output.uv = input.uv;
    
    return output;	
}
//���� ������ ����� tex�� �־��ش�.
Texture2D srcTex : register(t0);
//���� ������ �⺻������ �־� �ش�.
SamplerState samp : register(s0);

//�������� PS�� ��Ƽ� �������� ���̴�.
float4 PS(PixelInput input) : SV_Target
{
    float4 color = srcTex.Sample(samp, input.uv);
    
    if (color.a == 0.0f)
        discard;
    
    return color;
}