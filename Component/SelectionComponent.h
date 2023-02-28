#pragma once

class SelectionComponent : public Component
{
public:
	SelectionComponent(const UINT& slot = 0, const UINT& selection = 1, const Vector2& size = { gWinWidth, gWinHeight });

public:
	void Update() override;
	void Render() override;

public:
	void SetSelection(const UINT& selection) { SB->SetSelection(selection); }
	void SetTextureSize(const Vector2& size) { SB->SetTextureSize(size); }

private:
	unique_ptr<SelectionBuffer> SB;
	UINT slot = 0;
};