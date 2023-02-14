#include "stdafx.h"
#include "SelectionComponent.h"

SelectionComponent::SelectionComponent(const UINT& selection, const UINT& slot)
	:Component("Selection"), slot(slot)
{
	SB = make_unique<SelectionBuffer>();
	SetSelection(selection);
}

void SelectionComponent::Update()
{
	if (INPUT->Down('1'))
		SetSelection(1);
	else if (INPUT->Down('2'))
		SetSelection(2);
	else if (INPUT->Down('3'))
	{
		SetSelection(3);
	}
	else if (INPUT->Down('4'))
		SetSelection(4);
	else if (INPUT->Down('5'))
		SetSelection(5);
}

void SelectionComponent::Render()
{
	SB->SetPSBuffer(slot);
}

void SelectionComponent::SetSelection(const UINT& selection)
{
	SB->SetSelection(selection);
}
