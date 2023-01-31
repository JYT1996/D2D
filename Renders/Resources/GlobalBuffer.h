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

//색이라는 값을 넘겨주기 위해 ConstantBuffer의 파생클래스 ColorBuffer로 값을 넘겨줄 것이다.
class ColorBuffer : public ConstantBuffer
{	
	struct ColorStruct
	{
		//RGBA folat 값이 4개.
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
