#pragma once

class Scene3 : public Scene
{
public:
	void Init() override;
	void Destroy() override;

	void Update() override;
	void Render() override;

private:
	unique_ptr<ColorRect> rect1;
	unique_ptr<ColorRect> rect2;
	unique_ptr<Circle> circle;
	unique_ptr<FilledCircle> filledCircle;
};
