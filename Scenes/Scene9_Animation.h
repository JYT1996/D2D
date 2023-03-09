#pragma once

class Scene9 : public Scene
{
public:
	void Init() override;
	void Destroy() override;

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;

private:
	unique_ptr<TextureRect> background;
	unique_ptr<AnimationRect> animRect;
};