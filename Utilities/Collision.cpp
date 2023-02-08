#include "stdafx.h"
#include "Collision.h"

namespace Collision
{
	RECT::RECT(Vector2 position, Vector2 scale)
	{
		//좌하
		min = position - scale * 0.5f;
		//우상
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
	bool IntersectRectRect(const Object& object1, const Object& object2)
	{
		Vector2 rect1Pivot = object1.GetWorld()->GetPosition();
		Vector2 rect2Pivot = object2.GetWorld()->GetPosition();
		Vector2 distance = rect2Pivot - rect1Pivot;
		//rect1의 (0, 1) vector 단위vector
		Vector2 rect1Up = object1.GetWorld()->GetUpVector() * object1.GetWorld()->GetScale().y * 0.5;
		Vector2 rect1Right = object1.GetWorld()->GetRightVector() * object1.GetWorld()->GetScale().x * 0.5;

		Vector2 rect2Up = object2.GetWorld()->GetUpVector() * object2.GetWorld()->GetScale().y * 0.5;
		Vector2 rect2Right = object2.GetWorld()->GetRightVector() * object2.GetWorld()->GetScale().x * 0.5;
		
		//4개의 축을 사영해서 충돌인지 확인을 한다.
		//첫번째 축은 rect1의 RightVector
		float c1 = fabs(distance.Dot(object1.GetWorld()->GetRightVector()));

		float a1 = fabs(rect2Up.Dot(object1.GetWorld()->GetRightVector()))
			+ fabs(rect2Right.Dot(object1.GetWorld()->GetRightVector()));

		float b1 = object1.GetWorld()->GetScale().x * 0.5f;
			
		if (c1 > a1 + b1)
			return false;
		//두번째 축은 rect1의 UpVector
		float c2 = fabs(distance.Dot(object1.GetWorld()->GetUpVector()));

		float a2 = fabs(rect2Up.Dot(object1.GetWorld()->GetUpVector()))
			+ fabs(rect2Right.Dot(object1.GetWorld()->GetUpVector()));

		float b2 = object1.GetWorld()->GetScale().y * 0.5f;

		if (c2 > a2 + b2)
			return false;
		//세번째 축은 rect2의 RightVector
		float c3 = fabs(distance.Dot(object2.GetWorld()->GetRightVector()));

		float a3 = fabs(rect1Up.Dot(object2.GetWorld()->GetRightVector()))
			+ fabs(rect1Right.Dot(object2.GetWorld()->GetRightVector()));

		float b3 = object2.GetWorld()->GetScale().x * 0.5f;

		if (c3 > a3 + b3)
			return false;
		//네번째 축은 rect2의 UpVector
		float c4 = fabs(distance.Dot(object2.GetWorld()->GetUpVector()));

		float a4 = fabs(rect1Up.Dot(object2.GetWorld()->GetUpVector()))
			+ fabs(rect1Right.Dot(object2.GetWorld()->GetUpVector()));

		float b4 = object2.GetWorld()->GetScale().y * 0.5f;

		if (c4 > a4 + b4)
			return false;

		return true;
	}

	bool IntersectCircleCircle(const CIRCLE& circle1, const CIRCLE& circle2)
	{
		//거리가 원들의 반지름의 합보다 작으면 충돌이다.
		Vector2 distance = circle1.pivot - circle2.pivot;
		if (distance.Length() < circle1.radius + circle2.radius)
			return true;

		return false;
	}

	bool IntersectRectCircle(const RECT& rect, const CIRCLE& circle)
	{
		//사각형이 좌우로 반지름만큼 커진 후 원의 중심이 들어오면 충돌.
		//사각형이 상하로 반지름만큼 커진 후 원의 중심이 들어오면 충돌.
		//사각형의 꼭지점에서 원이랑 충돌이면 충돌.
		
		Vector2 rectPivot = (rect.min + rect.max) * 0.5f;
		Vector2 rectScale = rect.max - rect.min;
		RECT wRect(rectPivot, rectScale + Vector2(circle.radius * 2.0f, 0.0f));
		if (IntersectRectCoord(wRect, circle.pivot))
			return true;

		RECT hRect(rectPivot, rectScale + Vector2(0.0f, circle.radius * 2.0f));
		if (IntersectRectCoord(wRect, circle.pivot))
			return true;

		array<Vector2, 4> edges;
		edges[0] = rect.min;
		edges[1] = rect.max;
		edges[2] = Vector2(rect.min.x, rect.max.y);
		edges[3] = Vector2(rect.max.x, rect.min.y);
		for (const Vector2& edge : edges)
			if (IntersectCircleCoord(circle, edge))
				return true;

		return false;
	}
}