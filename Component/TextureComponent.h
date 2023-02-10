#pragma once

class TextureComponent : public Component
{
public:
	TextureComponent(const wstring& texturePath = L"", UINT slot = 0, const string& name = "Texture");
	TextureComponent(const TextureComponent& other) : TextureComponent(other.texturePath, other.slot, other.name) {};

public:
	wstring GetPath() { return texturePath; }
	ScratchImage* GetImage() { return &image; }

	void SetSRV(ComPtr<ID3D11ShaderResourceView> srv) { this->srv = srv; }
	void SetSRV(const wstring& texturePath);

public:
	void Render() override;

private:
	ComPtr<ID3D11ShaderResourceView> srv;
	wstring texturePath = L"";

	ScratchImage image;

	UINT slot = 0;
};
