#include "stdafx.h"
#include "AnimationRect.h"

AnimationRect::AnimationRect(const Vector2& position, const Vector2& scale, float rotation, const wstring& texturePath)
	: TextureRect(position, scale, rotation, texturePath)
{
	VB->Create(vertices, D3D11_USAGE_DYNAMIC);

	//CreateSamplerState
	{
		CD3D11_DEFAULT def;
		CD3D11_SAMPLER_DESC desc(def);

		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;

		HRESULT hr = DEVICE->CreateSamplerState(&desc, &sampleStater);
		CHECK(hr);
	}
}

void AnimationRect::Update()
{
	SUPER::Update();

	animator->Update();

	D3D11_MAPPED_SUBRESOURCE subResource;
	DC->Map(VB->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	{
		vertices[0].uv = Vector2(animator->GetCurrentFrame().x, animator->GetCurrentFrame().y + animator->GetTexelFrameSize().y);
		vertices[1].uv = animator->GetCurrentFrame();
		vertices[2].uv = animator->GetCurrentFrame() + animator->GetTexelFrameSize();
		vertices[3].uv = Vector2(animator->GetCurrentFrame().x + animator->GetTexelFrameSize().x, animator->GetCurrentFrame().y);
	}

	memcpy(subResource.pData, vertices.data(), sizeof(vertices[0])* vertices.size());
	DC->Unmap(VB->GetResource(), 0);
}

void AnimationRect::Render()
{
	DC->PSSetSamplers(0, 1, sampleStater.GetAddressOf());

	SUPER::Render();
}