#pragma once

class Scene4 : public Scene
{
public:
	void Init() override;
	void Destroy() override;

	void Update() override;
	void Render() override;

private:
	unique_ptr<TextureRect> rect1;	
};
