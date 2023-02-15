struct VertexInput
{
    float4 position : POSITION0;
    float2 uv : TEXCOORD0;
};

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
        
    }
    
        return color;
}