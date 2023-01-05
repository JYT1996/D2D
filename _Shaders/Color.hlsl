struct VertexInput
{
	//�ø�ƽ�� �̸� + �ε���
    //�̸� ���ؼ� CPU�� GPU�� ���� ���ش�.
	//float2�ε�, float4�� �� ������ ���̴����� ���� ���ϰ� ���� �Ѱ��ش�.
	//��İ��� �ϱ� ������ ���ϱ� ���ϰ� folat4�� ���� �Ѱ��ش�.
	float4 position : POSITION0;
	float4 color : COLOR0;
};

struct PixelInput
{
    float4 position : SV_Position0;
    float4 color : COLOR0;
};
//�������� VS�� ��Ƽ� �������� ���̴�.

PixelInput VS(VertexInput input)
{
    PixelInput output;	
	
    output.position = input.position;
    output.color = input.color;
    
    return output;	
}