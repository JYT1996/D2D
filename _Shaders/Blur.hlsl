#include "CBuffers.hlsl"

struct VertexInput
{
    float4 position : POSITION0;
    float2 uv : TEXCOORD0;
};

struct PixelInput
{
    float4 position : SV_POSITION0;
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
    
    float4 result = color;
    
    float2 arr[8] =
    {
        float2(-1, -1), float2(0, -1), float2(1, -1),
        float2(-1, 0),                 float2(1, 0), 
        float2(-1, 1), float2(0, 1),   float2(1, 1)
    };
    
    uint blurCount = 0;
    
    if (_selection == 2)
    {
        blurCount = 4;
    }
    else if (_selection == 3)
    {
        blurCount = 8;
    }
    else if (_selection == 4)
    {
        blurCount = 16;
    }
    else if (_selection == 5)
    {
        blurCount = 32;
    }
    
    for (uint blur = 0; blur < blurCount; ++blur)
    {
        for (uint i = 0; i < 8; ++i)
        {
            float x = arr[i].x * (float) blur / _textureSize.x;
            float y = arr[i].y * (float) blur / _textureSize.y;
            
            float2 uv = input.uv + float2(x, y);
            color += srcTex.Sample(samp, uv);
        }
    }
    
    color /= blurCount * 8 + 1;
    result = float4(color.rgb, 1);
    
    return result;
}