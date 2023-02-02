#pragma once

class Scene2 : public Scene
{
public:
	void Init() override;
	void Destroy() override;

	void Update() override;
	void Render() override;

private:
	unique_ptr<Line> hourLine;
	unique_ptr<Line> minLine;
	unique_ptr<Line> secLine;
	unique_ptr<Circle> clockCircle;
	SYSTEMTIME time = { 0 };
};
