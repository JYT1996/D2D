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
	//색을 가지고 있을 상수버퍼 ColorBuffer 
	unique_ptr<ColorBuffer> CB;
	//SetPSBuffer를 하려면 몇번 슬롯인지 정해야하기 때문에 필요하다.
	UINT slot = 0;
	
	Color color;
};
