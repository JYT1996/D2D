#include "stdafx.h"
#include "TextureRect.h"

TextureRect::TextureRect(const Vector2& position, const Vector2& scale, const float& rotation, const wstring& texturePath)
	: Drawable("TextureRect", position, scale, rotation, L"_Shaders/VertexTexture.hlsl")
{
	vertices.assign(4, VertexTexture());
	vertices[0].position = Vector2(-0.5f, -0.5f);
	vertices[0].uv = Vector2(0.0f, 1.0f);
	vertices[1].position = Vector2(-0.5f, 0.5f);
	vertices[1].uv = Vector2(0.0f, 0.0f);
	vertices[2].position = Vector2(0.5f, -0.5f);
	vertices[2].uv = Vector2(1.0f, 1.0f);
	vertices[3].position = Vector2(0.5f, 0.5f);
	vertices[3].uv = Vector2(1.0f, 0.0f);

	indices = { 0, 1, 2, 2, 1, 3 };

	VB->Create(vertices, D3D11_USAGE_IMMUTABLE);

	IB->Create(indices, D3D11_USAGE_IMMUTABLE);

	IL->Create(VertexTexture::descs, VertexTexture::count, VS->GetBlob());

	//CreateBlendState
	{
		D3D11_BLEND_DESC desc;
		ZeroMemory(&desc, sizeof(desc));

		desc.AlphaToCoverageEnable = false;
		desc.IndependentBlendEnable = false;

		desc.RenderTarget[0].BlendEnable = true;
		desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

		desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

		desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		HRESULT hr = DEVICE->CreateBlendState(&desc, &blendState);
		CHECK(hr);
	}

	AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
	AddComponent(make_shared<TextureComponent>(texturePath));
	AddComponent(make_shared<SelectionComponent>(1));
}

void TextureRect::Update()
{
	SUPER::Update();
}

void TextureRect::Render()
{
	SUPER::Render();

	if (Path::GetExtension(GetTexture()->GetPath()) == L"png")
		DC->OMSetBlendState(blendState.Get(), nullptr, 0xFFFFFFFF);

	DrawCall(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	DC->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);
}

void TextureRect::GUI(int ordinal)
{
	string objName = name + to_string(ordinal);
	string imgName = "Image : " + String::ToString(Path::GetFileName(GetTexture()->GetPath()));
	string shaderName = "Shader : " + String::ToString(Path::GetFileName(shaderPath));

	if (ImGui::BeginMenu(objName.c_str()))
	{
		ImGui::Text(objName.c_str());
		ImGui::Text(imgName.c_str());
		ImGui::Text(shaderName.c_str());

		if (ImGui::Button("ChangeImage", ImVec2(100, 30)))
			ChangeImageFunc();
		if (ImGui::Button("ChangeShader", ImVec2(100, 30)))
			ChangeShaderFunc();
		if (ImGui::InputText("InputText", text, sizeof(text), ImGuiInputTextFlags_EnterReturnsTrue))
			SaveTextAsFile(text);

		SUPER::GUI();

		ImGui::EndMenu();
	}
}

void TextureRect::ChangeImageFunc(const wstring& path)
{
	if (path.length() < 1)
	{
		function<void(wstring)> func = bind(&TextureRect::ChangeImageFunc, this, placeholders::_1);
		Path::OpenFileDialog(L"", Path::ImageFilter, L"_Textures/", func, gHandle);
	}
	else
	{
		GetTexture()->SetSRV(path);
	}
}

void TextureRect::ChangeShaderFunc(const wstring& path)
{
	if (path.length() < 1)
	{
		function<void(wstring)> func = bind(&TextureRect::ChangeShaderFunc, this, placeholders::_1);
		Path::OpenFileDialog(L"", Path::ShaderFilter, L"_Shaders/", func, gHandle);
	}
	else
	{
		SetShader(path);
	}
}

void TextureRect::SaveTextAsFile(const string& text, const wstring& path)
{
	if (path.length() < 1)
	{
		function<void(wstring)> func = bind(&TextureRect::SaveTextAsFile, this, text, placeholders::_1);
		Path::SaveFileDialog(L"", Path::TextFilter, L"./", func, gHandle);
	}
	else
	{
		ofstream writeFile(path.c_str());
		if (writeFile.is_open())
		{
			writeFile << text << '\n';
			writeFile.clear();
		}
		writeFile.close();
	}
}
