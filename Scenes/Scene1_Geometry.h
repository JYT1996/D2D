#pragma once

class Scene1 : public Scene
{
public:
	void Init() override;
	void Destroy() override;

	void Update() override;
	void PreRender() override {}
	void Render() override;
	void PostRender() override {}

private:
	unique_ptr<ColorRect> rect;
	unique_ptr<Line> line;
	unique_ptr<Circle> circle;
	unique_ptr<FilledCircle> filledCircle;
};
