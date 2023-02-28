#pragma once

class VertexShader : public IShader
{
public:
	ID3D11VertexShader* GetResource() const { return shader.Get(); }
	ID3DBlob* GetBlob() const { return blob.Get(); }

public:
	void Create(const wstring& path, const string& entryName) override;
	void Clear() override;
	void SetShader() override;

private:
	ComPtr<ID3DBlob> blob;
	ComPtr<ID3D11VertexShader> shader;
};