struct VertexInput
{
    float4 position : POSITION0;
	float4 color : COLOR0;
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
    float4 color : COLOR0;
};

//진입점을 VS로 잡아서 컴파일할 것이다.
PixelInput VS(VertexInput input)
{
    PixelInput output;
	
    output.position = mul(input.position, _world);
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _proj);
    output.color = input.color;
    
    return output;	
}

//진입점을 PS로 잡아서 컴파일할 것이다.
float4 PS(PixelInput input) : SV_Target
{
    return input.color;
}