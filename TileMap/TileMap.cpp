#include "stdafx.h"
#include "TileSet.h"
#include "TileMap.h"

TileMap::TileMap(const Vector2& position, const Vector2& scale, float rotation, UINT tileXCount, UINT tileYCount, const wstring& tileSetPath, UINT spacing)
	:Drawable("TileMap", position, scale, rotation, L"_Shaders/VertexTile.hlsl"), spacing(spacing)
{
	tileSet = make_unique<TileSet>(tileSetPath, tileXCount, tileYCount);

	width = (UINT)scale.x / spacing;
	height = (UINT)scale.y / spacing;

	GenerateTileMap(width, height, spacing);

	vertices.assign(4, VertexColorTexture());

	vertices[0].position = Vector2();
	vertices[1].position = Vector2(0, (float)spacing);
	vertices[2].position = Vector2((float)spacing, 0);
	vertices[3].position = Vector2((float)spacing, (float)spacing);

	vertices[0].uv = Vector2(0, 1);
	vertices[1].uv = Vector2(0, 0);
	vertices[2].uv = Vector2(1, 1);
	vertices[3].uv = Vector2(1, 0);
	
	for (auto& vertex : vertices)
		vertex.color = BLACK;

	indices = { 0, 1, 2, 2, 1, 3 };
	
	VB->Create(vertices, D3D11_USAGE_DYNAMIC);
	IB->Create(indices, D3D11_USAGE_IMMUTABLE);

	IL->Create(VertexColorTexture::descs, VertexColorTexture::count, VS->GetBlob());

	SetSRV(tileSet->srv);
}

void TileMap::Update()
{
	SUPER::Update();

	if (INPUT->Press(VK_LBUTTON))
	{
		Vector2 mPos = CAMERA->UnProject(INPUT->GetMousePosition());
		Tile* tile = GetTile(mPos);

		if (tile)
		{
			tile->uvStart = tileSet->selectedStartUV;
			tile->uvEnd = tileSet->selectedStartUV + tileSet->texelTileSize;
		}
	}
}

void TileMap::Render()
{
	SUPER::Render();

	DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	DC->PSSetShaderResources(0, 1, srv.GetAddressOf());

	for (UINT y = 0; y < height; ++y)
	{
		for (UINT x = 0; x < width; ++x)
		{
			Tile& tile = tiles[y][x];

			D3D11_MAPPED_SUBRESOURCE subResourec;

			DC->Map(VB->GetResource(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResourec);
			{
				vertices[0].uv = Vector2(tile.uvStart.x, tile.uvEnd.y);
				vertices[1].uv = tile.uvStart;
				vertices[2].uv = tile.uvEnd;
				vertices[3].uv = Vector2(tile.uvEnd.x, tile.uvStart.y);
				memcpy(subResourec.pData, vertices.data(), sizeof(vertices[0]) * vertices.size());
			}
			DC->Unmap(VB->GetResource(), 0);

			GetWorld()->SetWorld(XMMatrixTranslationFromVector(tile.pos + GetWorld()->GetPosition()));
			GetWorld()->Render();

			DC->DrawIndexed(IB->GetCount(), 0, 0);
		}
	}
}

void TileMap::GUI()
{
	tileSet->GUI();
}

void TileMap::GenerateTileMap(UINT width, UINT height, UINT spacing)
{
	if (width == 0 || height == 0 || spacing == 0)
	{
		assert(false);
		return;
	}

	tiles.clear();
	tiles.assign(height, vector<Tile>());
	for (UINT y = 0; y < height; ++y)
	{
		tiles[y].assign(width, Tile());
		for (UINT x = 0; x < width; ++x)
		{
			tiles[y][x].pos = Vector2((float)x, (float)y) * (float)spacing;
		}
	}
}

Tile* TileMap::GetTile(const Vector2& unprojectedMousePos)
{
	UINT x = ((int)unprojectedMousePos.x) / spacing;
	UINT y = ((int)unprojectedMousePos.y) / spacing;

	if (x >= width || y >= height || x < 0 || y < 0)
		return nullptr;

	return &tiles[y][x];
}
