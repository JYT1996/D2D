struct VertexInput
{
	//시멘틱스 이름 + 인덱스
    //이를 통해서 CPU와 GPU를 연결 해준다.
	//float2인데, float4가 된 이유는 쉐이더에서 쓰기 편하게 값을 넘겨준다.
	//행렬곱을 하기 때문에 곱하기 편하게 folat4로 값을 넘겨준다.
	float4 position : POSITION0;
	float4 color : COLOR0;
};

struct PixelInput
{
    float4 position : SV_Position0;
    float4 color : COLOR0;
};
//진입점을 VS로 잡아서 컴파일할 것이다.

PixelInput VS(VertexInput input)
{
    PixelInput output;	
	
    output.position = input.position;
    output.color = input.color;
    
    return output;	
}