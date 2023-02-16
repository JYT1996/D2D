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
    float3 grayscale = 0;
    float3 sepia = 0;
    
    if (_selection == 1)
        ;
    else if (_selection == 2)
    {
        grayscale = (color.r + color.g + color.b) / 3.0f;
        color = float4(grayscale, 1);
    }
    else if (_selection == 3)
    {
        //MS의 grayscale의 rgb비율
        grayscale = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
        color = float4(grayscale, 1);
    }
    else if (_selection == 4)
    {
        sepia.r = dot(color.rgb, float3(0.393f, 0.769f, 0.189f));
        sepia.g = dot(color.rgb, float3(0.349f, 0.686f, 0.168f));
        sepia.b = dot(color.rgb, float3(0.272f, 0.534f, 0.131f));
        color = float4(sepia.rgb, 1);
    }
    else if (_selection == 5)
    {
        float4 lt = srcTex.Sample(samp, 2 * input.uv);
        float4 rt = srcTex.Sample(samp, 2 * float2(1 - input.uv.x, input.uv.y));
        float4 lb = srcTex.Sample(samp, 2 * float2(input.uv.x, 1 - input.uv.y));
        
        float4 rblt = srcTex.Sample(samp, 4 * float2(input.uv.x - 0.5f, input.uv.y - 0.5f));
        float4 rbrt = srcTex.Sample(samp, 4 * float2(1 - input.uv.x, input.uv.y - 0.5f));
        float4 rblb = srcTex.Sample(samp, 4 * float2(input.uv.x - 0.5f, 1 - input.uv.y));
        float4 rbrb = srcTex.Sample(samp, 4 * (1 - input.uv));
        
        if (input.uv.x < 0.5f && input.uv.y < 0.5f)
            color = lt;
        if (input.uv.x > 0.5f && input.uv.y < 0.5f)
        {
            color = rt;
            grayscale = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
            color = float4(grayscale, 1);
        }
        if (input.uv.x < 0.5f && input.uv.y > 0.5f)
        {
            color = lb;
            sepia.r = dot(color.rgb, float3(0.393f, 0.769f, 0.189f));
            sepia.g = dot(color.rgb, float3(0.349f, 0.686f, 0.168f));
            sepia.b = dot(color.rgb, float3(0.272f, 0.534f, 0.131f));
            color = float4(sepia.rgb, 1);
        }
        if (input.uv.x > 0.5f && input.uv.y > 0.5f)
        {
            if (input.uv.x < 0.75f && input.uv.y < 0.75f)
            {
                color = rblt;
            }
            if (input.uv.x > 0.75f && input.uv.y < 0.75f)
            {
                color = rbrt;
                grayscale = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
                color = float4(grayscale, 1);
            }
            if (input.uv.x < 0.75f && input.uv.y > 0.75f)
            {
                color = rblb;
                sepia.r = dot(color.rgb, float3(0.393f, 0.769f, 0.189f));
                sepia.g = dot(color.rgb, float3(0.349f, 0.686f, 0.168f));
                sepia.b = dot(color.rgb, float3(0.272f, 0.534f, 0.131f));
                color = float4(sepia.rgb, 1);
            }
            if (input.uv.x > 0.75f && input.uv.y > 0.75f)
            {
                color = rbrb;
            }
        }
        
        if (input.uv.x > 0.499f && input.uv.x < 0.501f)
            color = float4(1, 1, 1, 1);
        if (input.uv.y > 0.499f && input.uv.y < 0.501f)
            color = float4(1, 1, 1, 1);
        
        if (input.uv.x > 0.7499f && input.uv.x < 0.751f && input.uv.y > 0.5f)
            color = float4(1, 1, 1, 1);
        if (input.uv.y > 0.7499f && input.uv.y < 0.752f && input.uv.x > 0.5f)
            color = float4(1, 1, 1, 1);
    }
    
    return color;
}