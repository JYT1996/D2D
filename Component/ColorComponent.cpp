#include "stdafx.h"
#include "ColorComponent.h"

ColorComponent::ColorComponent(const Color& color, const UINT& slot, const string& compName)
	: Component(compName), color(color), slot(slot)
{
	CB = make_unique<ColorBuffer>();
	CB->SetColor(color);
}
//버퍼에 원하는 색을 넣는다.
void ColorComponent::SetColor(const Color& color)
{
	this->color = color;
	CB->SetColor(color);
}
//실제로 PS에 값을 넘겨줘서 색을 결정하게 한다.
void ColorComponent::Render()
{
	CB->SetPSBuffer(slot);
}
