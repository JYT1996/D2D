#include "CBuffers.hlsl"

struct VertexInput
{
    float4 position : POSITION0;
    float2 uv : TEXCOORD0;
};

struct PixelInput
{
    float4 position : SV_Position0;
    float2 uv : TEXCOORD0;
};

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

float4 PS(PixelInput input) : SV_Target
{
    float4 color = srcTex.Sample(samp, input.uv);
    
    float2 dist = input.uv - 0.5f;
    
    if (_selection == 1)
        ;
    else if (_selection == 2)
    {
        color.rgb *= 1 - dot(dist, dist) * 5;
    }
    else if (_selection == 3)
    {
        color.rgb *= 1 - dot(dist, dist) * 10;
    }
    else if (_selection == 4)
    {
        color.rgb *= 1 - dot(dist, dist) * 15;
    }
    
    return color;
}