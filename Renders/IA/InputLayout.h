#pragma once

class InputLayout
{
public:
	ID3D11InputLayout* GetResource() const { return inputLayout.Get(); }

	void Create(const D3D11_INPUT_ELEMENT_DESC* desc, const UINT& count, const ComPtr<ID3DBlob>& blob);
	void SetIA();

private:
	ComPtr<ID3D11InputLayout> inputLayout;
};