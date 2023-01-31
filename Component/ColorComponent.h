#pragma once

class ColorComponent : public Component
{
public:
	ColorComponent(const Color& color, const UINT& slot, const string& compName = "Color");
	
public:
	Color GetColor() { return color; }

	void SetColor(const Color& color);

public:
	void Update() override {};
	void Render() override;

private:
	//���� ������ ���� ������� ColorBuffer 
	unique_ptr<ColorBuffer> CB;
	//SetPSBuffer�� �Ϸ��� ��� �������� ���ؾ��ϱ� ������ �ʿ��ϴ�.
	UINT slot = 0;
	
	Color color;
};
