struct VertexInput
{
	float4 position : POSITION0;
	float2 uv : TEXCOORD0;
};
//값을 넣어진 순서대로 쉐이더에서 받아줘야 한다.
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

//진입점을 VS로 잡아서 컴파일할 것이다.
PixelInput VS(VertexInput input)
{
    PixelInput output;
	
    output.position = mul(input.position, _world);
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _proj);
    
    output.uv = input.uv;
    
    return output;	
}
//현재 저장한 고양이 tex를 넣어준다.
Texture2D srcTex : register(t0);
//값이 없으면 기본값으로 넣어 준다.
SamplerState samp : register(s0);

//진입점을 PS로 잡아서 컴파일할 것이다.
float4 PS(PixelInput input) : SV_Target
{
    float4 color = srcTex.Sample(samp, input.uv);
    
    if (color.a == 0.0f)
        discard;
    
    return color;
}