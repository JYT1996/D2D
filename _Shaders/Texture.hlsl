struct VertexInput
{
	float4 position : POSITION0;
	float2 uv : TEXCOORD0;
};

cbuffer TransformBuffer : register(b0)
{
    matrix _world;
    matrix _view;
    matrix _proj;
}

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
    
    if (color.a == 0.0f)
        discard;
    
    return color;
}