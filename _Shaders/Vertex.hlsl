//Vertex.hlsl은 상수버퍼로 color값을 넘겨 줄 것이기 떄문에 vertexBuffer에서 받아오던 color를 삭제한다.
struct VertexInput
{
    float4 position : POSITION0;
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
};

//진입점을 VS로 잡아서 컴파일할 것이다.
PixelInput VS(VertexInput input)
{
    PixelInput output;
	
    output.position = mul(input.position, _world);
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _proj);
    
    return output;	
}
//상수버퍼에서 값을 받아오기 위해 register설정을 해준다.
cbuffer ColorBuffer : register(b0)
{
    float4 _color;
}

//진입점을 PS로 잡아서 컴파일할 것이다.
float4 PS(PixelInput input) : SV_Target
{
    return _color;
}