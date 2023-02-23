#include "stdafx.h"
#include "TextureRect.h"
TextureRect::TextureRect(const Vector2& position, const Vector2& scale, const float& rotation, const wstring& texturePath)
	: Drawable("Texture", position, scale, rotation, L"_Shaders/VertexTexture.hlsl")
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

	vertexBuffer->Create(vertices, D3D11_USAGE_IMMUTABLE);

	indexBuffer->Create(indices, D3D11_USAGE_IMMUTABLE);

	inputLayout->Create(VertexTexture::descs, VertexTexture::count, vertexShader->GetBlob());

	AddComponent(make_shared<ColliderComponent>(ColliderType::RECT));
	AddComponent(make_shared<TextureComponent>(texturePath));
}

void TextureRect::Update()
{
	SUPER::Update();
}


void TextureRect::Render()
{
	SUPER::Render();

	DrawCall(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void TextureRect::GUI(int ordinal)
{
	string objName = name + to_string(ordinal);
	string imgName = "Image : " + String::ToString(Path::GetFileName(GetTexture()->GetPath()));
	string shaderName = "Shader : " + String::ToString(Path::GetFileName(shaderPath));
	//Begin�� ����â�� ����� ���̰� BeginMenu�� �� â�� �߰����� â�� ����� ���̴�.
	//EndMenu�� ���ʿ��� ����� �Ѵ�.
	if (ImGui::BeginMenu(objName.c_str()))
	{
		ImGui::Text(objName.c_str());
		ImGui::Text(imgName.c_str());
		ImGui::Text(shaderName.c_str());
		
		if (ImGui::Button("ChangeImage", ImVec2(100, 30)))
			ChangeImageFunc();

		if (ImGui::Button("ChangeShader", ImVec2(100, 30)))
			ChangeShaderFunc();

		SUPER::GUI();

		ImGui::EndMenu();
	}
}

void TextureRect::ChangeImageFunc(const wstring& path)
{
	//���ڿ��� ����ִ� ��Ȳ
	if (path.length() < 1)
	{
		//�׷��� dialog�� ��� �̹����� ������ �� �ִ� â�� �����.
		//�̶� ����ϴ� Filter�� Path���� ���� imageFilter�� ����ϰ�, ���� directory�� _Textures/�̴�.
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
		this->SetShader(path);
	}
}

void TextureRect::SaveTextAsFile(const string& text, const wstring& path)
{
}
