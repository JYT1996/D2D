#pragma once

class SelectionComponent : public Component
{
public:
	SelectionComponent(const UINT& selection = 1, const UINT& slot = 0);

public:
	void Update() override;
	void Render() override;

public:
	void SetSelection(const UINT& selection);


private:
	unique_ptr<SelectionBuffer> SB;
	UINT slot = 0;


};
