#pragma once

class Scene5 : public Scene
{
public:
	void Init() override;
	void Destroy() override;

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override {}

private:
	unique_ptr<ColorRect> rect1;
	unique_ptr<ColorRect> rect2;

	unique_ptr<RenderTexture> RTT;
	//unique_ptr<TextureRect> renderingTexture;
	vector<unique_ptr<TextureRect>> test;
};