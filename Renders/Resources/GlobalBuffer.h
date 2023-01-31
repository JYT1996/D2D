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

//���̶�� ���� �Ѱ��ֱ� ���� ConstantBuffer�� �Ļ�Ŭ���� ColorBuffer�� ���� �Ѱ��� ���̴�.
class ColorBuffer : public ConstantBuffer
{	
	struct ColorStruct
	{
		//RGBA folat ���� 4��.
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
