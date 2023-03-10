#pragma once

#include "stdafx.h"

class WorldBuffer : public ConstantBuffer
{
	struct WorldStruct
	{
		Matrix world;
	};

public:
	WorldBuffer() : ConstantBuffer(&data, sizeof(WorldStruct)) {}

	void SetWorld(const Matrix& world)
	{
		data.world = XMMatrixTranspose(world);
	}

private:
	WorldStruct data;
};

class ViewProjectionBuffer : public ConstantBuffer
{
	struct WorldSViewProjectionStruct
	{
		Matrix view;
		Matrix projection;
	};

public:
	ViewProjectionBuffer() : ConstantBuffer(&data, sizeof(WorldSViewProjectionStruct)) {}

	void SetView(const Matrix& view)
	{
		data.view = XMMatrixTranspose(view);
	}

	void SetProjection(const Matrix& projection)
	{
		data.projection = XMMatrixTranspose(projection);
	}

private:
	WorldSViewProjectionStruct data;
};

class ColorBuffer : public ConstantBuffer
{	
	struct ColorStruct
	{
		Color color;
	};

public:
	ColorBuffer() : ConstantBuffer(&data, sizeof(ColorStruct)) {}
	
	void SetColor(const Color& color)
	{
		data.color = color;
	}

private:
	ColorStruct data;
};

class SelectionBuffer : public ConstantBuffer
{
	struct SelectionStruct
	{
		UINT selection = 1;
		Vector2 textureSize = { gWinWidth, gWinHeight };
		UINT dummy = 0;
	};

public:
	SelectionBuffer() : ConstantBuffer(&data, sizeof(SelectionStruct)) {}

	void SetSelection(const UINT& selection)
	{
		data.selection = selection;
	}
	void SetTextureSize(const Vector2& size)
	{
		data.textureSize = size;
	}

private:
	SelectionStruct data;
};