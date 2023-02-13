#include "stdafx.h"
#include "RenderTexture.h"

void RenderTexture::Initialize()
{
	D3D11_TEXTURE2D_DESC textureDesc;
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;

	HRESULT hr;

	ZeroMemory(&textureDesc, sizeof(textureDesc));
	ZeroMemory(&rtvDesc, sizeof(rtvDesc));
	ZeroMemory(&srvDesc, sizeof(srvDesc));

	textureDesc.Width = (UINT)gWinWidth;
	textureDesc.Height = (UINT)gWinHeight;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;	
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	hr = DEVICE->CreateTexture2D(&textureDesc, nullptr, &renderTargetTexture);
	CHECK(hr);

	rtvDesc.Format = textureDesc.Format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Texture2D.MipSlice = 0;
	
	hr = DEVICE->CreateRenderTargetView(renderTargetTexture.Get(), &rtvDesc, &rtv);
	CHECK(hr);

	srvDesc.Format = textureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	hr = DEVICE->CreateShaderResourceView(renderTargetTexture.Get(), &srvDesc, &srv);
	CHECK(hr);
}

void RenderTexture::RenderToTexture()
{
	DC->OMSetRenderTargets(1, rtv.GetAddressOf(), nullptr);
	DC->ClearRenderTargetView(rtv.Get(), GRAPHICS->GetClearColor());
}

void RenderTexture::SaveTexture(const wstring& path)
{
	ScratchImage image;
	CaptureTexture(DEVICE.Get(), DC.Get(), renderTargetTexture.Get(), image);

	wstring ext = path.substr(path.find_last_of(L".") + 1);
	WICCodecs extCodec = WIC_CODEC_BMP;
	if (ext == L"jpg" && ext == L"jpeg")
		extCodec = WIC_CODEC_JPEG;
	else if (ext == L"png")
		extCodec = WIC_CODEC_PNG;
	else if (ext == L"gif")
		extCodec = WIC_CODEC_GIF;

	SaveToWICFile(image.GetImages(), image.GetImageCount(), WIC_FLAGS_NONE, GetWICCodec(extCodec), path.c_str());
}
