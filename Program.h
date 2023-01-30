#pragma once

class Program
{
public:
	Program();

public:
	void SetGlobalBuffer();

public:
	void Update();
	void Render();	

public:
	unique_ptr<ColorRect> rect;
	unique_ptr<Line> line;
	unique_ptr<Circle> circle;
	unique_ptr<FilledCircle> filledCircle;

private:
	unique_ptr<ViewProjectiondBuffer> VPBuffer;
	Matrix view, projection;	
};