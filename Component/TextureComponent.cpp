#include "stdafx.h"
#include "TextureComponent.h"

TextureComponent::TextureComponent(const wstring& texturePath, UINT slot, const string& name)
	: Component(name), texturePath(texturePath), slot(slot)
{
	if (texturePath != L"")
		SetSRV(texturePath);
}

void TextureComponent::SetSRV(const wstring& texturePath)
{
	this->texturePath = texturePath;

	LoadFromWICFile(texturePath.c_str(), WIC_FLAGS_NONE, nullptr, image);

	HRESULT hr = CreateShaderResourceView(DEVICE.Get(), image.GetImages(), image.GetImageCount(), image.GetMetadata(), &srv);
	CHECK(hr);
}

void TextureComponent::Render()
{
	DC->PSSetShaderResources(slot, 1, srv.GetAddressOf());
}
