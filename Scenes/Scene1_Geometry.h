#pragma once

class Scene1 : public Scene
{
public:
	void Init() override;
	void Destroy() override;

	void Update() override;
	void Render() override;

private:
	unique_ptr<ColorRect> rect;
	unique_ptr<Line> rect2;
	unique_ptr<Circle> circle;
	unique_ptr<FilledCircle> filledCircle;
};
