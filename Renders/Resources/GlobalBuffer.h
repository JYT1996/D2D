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


class ViewProjectiondBuffer : public ConstantBuffer
{
	struct WorldSViewProjectionStruct
	{
		Matrix view;
		Matrix projection;
	};

public:
	ViewProjectiondBuffer() : ConstantBuffer(&data, sizeof(WorldSViewProjectionStruct)) {}

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
		//shader는 16byte단위로 데이터를 전달받는다. 
		//그래서 16byte가 되게끔 dummy 자료형을 넣는다.
		UINT selection = 1;
		Vector3 dummy;
	};

public:
	SelectionBuffer() : ConstantBuffer(&data, sizeof(SelectionBuffer)) {}

	void SetSelection(const UINT& selection)
	{
		data.selection = selection;
	}

private:
	SelectionStruct data;
};