#pragma once

class ColorComponent : public Component
{
public:
	ColorComponent(const string& name = "Color");
	
public:

public:
	Color GetColor() { return this->color; }
	void SetColor(Color color);

private:
	Color color;

};
