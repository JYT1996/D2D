#pragma once

class Program
{
public:
	Program();
	~Program();

public:
	void Update();
	void Render();

private:
	unique_ptr<Rect> rect1;
	unique_ptr<Rect> rect2;
	
	bool check = false;
};