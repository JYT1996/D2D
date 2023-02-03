#include "stdafx.h"
#include "Collision.h"

namespace Collision
{
	RECT::RECT(Vector2 position, Vector2 scale)
	{
		//좌상
		min = position - scale * 0.5f;
		//우하단
		max = position + scale * 0.5f;
	}
	//원으로 가정하고 만든다.
	CIRCLE::CIRCLE(Vector2 position, Vector2 scale)
	{
		pivot = position;
		radius = scale.x * 0.5f;
	}

	bool IntersectRectCoord(const RECT& rect, const Vector2& coord)
	{
		if (rect.min.x < coord.x && coord.x < rect.max.x
			&& rect.min.y < coord.y && coord.y < rect.max.y)
		{
			return true;
		}
		return false;
	}

	bool IntersectCircleCoord(const CIRCLE& circle, const Vector2& coord)
	{
		Vector2 distance = circle.pivot - coord;
		if (distance.Length() < circle.radius)
		{
			return true;
		}
		return false;
	}

	bool IntersectRectRect(const RECT& rect1, const RECT& rect2)
	{
		if (rect1.min.x < rect2.max.x &&
			rect1.max.x > rect2.min.x &&
			rect1.min.y < rect2.max.y &&
			rect1.max.y > rect2.min.y)
		{
			return true;
		}
		return false;
	}
	//내적을 이용해서 값을 구한다.
	//회전된 도형들의 거리벡터를 구한다.
	//
	bool IntersectRectRect(const Object& object1, const Object& object2)
	{

		return false;
	}

	bool IntersectCircleCircle(const CIRCLE& circle1, const CIRCLE& circle2)
	{
		return false;
	}

	bool IntersectRectCircle(const RECT& rect, const CIRCLE& circle)
	{
		return false;
	}
}