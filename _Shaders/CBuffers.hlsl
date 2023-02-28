////////////////////////VertexShader//////////////////////
cbuffer World : register(b0)
{
	matrix _world;
}

cbuffer ViewProjection : register(b1)
{
	matrix _view;
	matrix _proj;
}

////////////////////////PixelShader//////////////////////
cbuffer ColorBuffer : register(b0)
{
	float4 _color;
}

cbuffer SelectionBuffer : register(b1)
{
	uint _selection;
	float2 _textureSize;
}