#pragma once

class Scene2 : public Scene
{
public:
	void Init() override;
	void Destroy() override;

	void Update() override;
	void PreRender() override {}
	void Render() override;
	void PostRender() override {}

private:
	SYSTEMTIME time = { 0 };

	unique_ptr<Circle> clock;

	unique_ptr<Line> hour;
	unique_ptr<Line> min;
	unique_ptr<Line> sec;
};
