#include "stdafx.h"
#include "ColorComponent.h"

ColorComponent::ColorComponent(const Color& color, const UINT& slot, const string& compName)
	: Component(compName), color(color), slot(slot)
{
	CB = make_unique<ColorBuffer>();
	CB->SetColor(color);
}
//���ۿ� ���ϴ� ���� �ִ´�.
void ColorComponent::SetColor(const Color& color)
{
	this->color = color;
	CB->SetColor(color);
}
//������ PS�� ���� �Ѱ��༭ ���� �����ϰ� �Ѵ�.
void ColorComponent::Render()
{
	CB->SetPSBuffer(slot);
}
