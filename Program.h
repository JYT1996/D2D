#pragma once

class Program
{
public:
	Program();
	~Program();

public:
	void SetGlobalBuffer();

public:
	void Update();
	void Render();	

public:
	unique_ptr<ColorRect> rect;

private:
	unique_ptr<ViewProjectiondBuffer> VPBuffer;
	Matrix view, projection;	
};