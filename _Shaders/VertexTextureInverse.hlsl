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
	
	if (_selection == 1)
		;
	else if (_selection == 2)
		color = srcTex.Sample(samp, float2(1 - input.uv.x, input.uv.y));
	else if (_selection == 3)
	{
		float4 l = srcTex.Sample(samp, input.uv);
		float4 r = srcTex.Sample(samp, float2(input.uv.x - 0.5f, input.uv.y));
		
		if (input.uv.x < 0.5f)
			color = l;
		if (input.uv.x > 0.5f)
			color = r;
		
		if (input.uv.x > 0.499f && input.uv.x < 0.501f)
			color = float4(1, 1, 1, 1);
	}
	else if (_selection == 4)
	{
		float4 lt = srcTex.Sample(samp, 2 * input.uv);
		float4 rt = srcTex.Sample(samp, 2 * float2(1 - input.uv.x, input.uv.y));
		float4 lb = srcTex.Sample(samp, 2 * float2(input.uv.x, 1 - input.uv.y));
		float4 rb = srcTex.Sample(samp, 2 * float2(1 - input.uv.x, 1 - input.uv.y));
		
		if (input.uv.x < 0.5f && input.uv.y < 0.5f)
			color = lt;
		if (input.uv.x > 0.5f && input.uv.y < 0.5f)
			color = rt;
		if (input.uv.x < 0.5f && input.uv.y > 0.5f)
			color = lb;
		if (input.uv.x > 0.5f && input.uv.y > 0.5f)
			color = rb;
		
		if (input.uv.x > 0.499f && input.uv.x < 0.501f)
			color = float4(1, 1, 1, 1);
		if (input.uv.y > 0.499f && input.uv.y < 0.501f)
			color = float4(1, 1, 1, 1);
	}
	
	return color;
}