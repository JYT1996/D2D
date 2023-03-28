#pragma once

struct Tile
{
	Vector2 pos;
	Vector2 uvStart;
	Vector2 uvEnd;
	Color color;
};

class TileMap : public Drawable
{
public:
	TileMap(const Vector2& position, const Vector2& scale, float rotation, UINT tileXCount, UINT tileYCount, const wstring& tileSetPath = L"", UINT spacing = 40);

	void SetSRV(const ComPtr<ID3D11ShaderResourceView>& srv) { this->srv = srv; }
	void Update() override;
	void Render() override;

	void GUI();
	
private:
	void GenerateTileMap(UINT width, UINT height, UINT spacing);
	Tile* GetTile(const Vector2& unprojectedMousePos);
	
private:
	UINT width = 0, height = 0;
	UINT spacing = 0;

	vector<VertexColorTexture> vertices;
	vector<UINT> indices;
	vector<vector<Tile>> tiles;

	ComPtr<ID3D11ShaderResourceView> srv;

	unique_ptr<class TileSet> tileSet;
};