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

Texture2D srcTex : register(t0);
SamplerState samp : register(s0);

cbuffer SelectionBuffer : register(b0)
{
    uint _selection;
}

float4 PS(PixelInput input) : SV_Target
{
    //�ƹ��͵� ���� ���� ��� ������ ��.
    float4 color = srcTex.Sample(samp, input.uv);
    
    if (_selection == 1)
        ;
    else if (_selection == 2)
        color = srcTex.Sample(samp, float2(1 - input.uv.x, input.uv.y));
    else if (_selection == 3)
    {   
        if (input.uv.x <= 0.5f)
            ;
        else        
            color = srcTex.Sample(samp, float2(0.5f - (input.uv.x - 0.5f), input.uv.y));
    }
    else if (_selection == 4)
    {
        if (input.uv.y <= 0.5f && input.uv.x <= 0.5f)
            color = srcTex.Sample(samp, float2(input.uv.x, 0.5f - input.uv.y) * 2.0f);
        else if (input.uv.y >= 0.5f && input.uv.x <= 0.5f)
            color = srcTex.Sample(samp, float2(input.uv.x, input.uv.y - 0.5f) * 2.0f);
        else if (input.uv.y <= 0.5f && input.uv.x >= 0.5f)
            color = srcTex.Sample(samp, float2(0.5f - (input.uv.x - 0.5f), 0.5f - input.uv.y) * 2.0f);
        else if (input.uv.y >= 0.5f && input.uv.x >= 0.5f)
            color = srcTex.Sample(samp, float2(0.5f - (input.uv.x - 0.5f), input.uv.y - 0.5f) * 2.0f);
    }    
    return color;
}