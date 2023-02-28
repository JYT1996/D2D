#include "stdafx.h"
#include "Collision.h"

namespace Collision
{
	RECT::RECT(Vector2 position, Vector2 scale)
	{
		min = position - scale * 0.5f;
		max = position + scale * 0.5f;
	}

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

	bool IntersectRectRect(const Object& object1, const Object& object2)
	{
		Vector2 rect1Pivot = object1.GetWorld()->GetPosition();
		Vector2 rect2Pivot = object2.GetWorld()->GetPosition();
		Vector2 distance = rect2Pivot - rect1Pivot;
	
		Vector2 rect1Up = object1.GetWorld()->GetUpVector() * object1.GetWorld()->GetScale().y * 0.5f;
		Vector2 rect1Right = object1.GetWorld()->GetRightVector() * object1.GetWorld()->GetScale().x * 0.5f;

		Vector2 rect2Up = object2.GetWorld()->GetUpVector() * object2.GetWorld()->GetScale().y * 0.5f;
		Vector2 rect2Right = object2.GetWorld()->GetRightVector() * object2.GetWorld()->GetScale().x * 0.5f;
		
		float c = fabs(distance.Dot(object1.GetWorld()->GetRightVector()));

		float a = fabs(rect2Up.Dot(object1.GetWorld()->GetRightVector()))
			+ fabs(rect2Right.Dot(object1.GetWorld()->GetRightVector()));

		float b = object1.GetWorld()->GetScale().x * 0.5f;
			
		if (c > a + b)
			return false;

		c = fabs(distance.Dot(object1.GetWorld()->GetUpVector()));

		a = fabs(rect2Up.Dot(object1.GetWorld()->GetUpVector()))
			+ fabs(rect2Right.Dot(object1.GetWorld()->GetUpVector()));

		b = object1.GetWorld()->GetScale().y * 0.5f;

		if (c > a + b)
			return false;

		c = fabs(distance.Dot(object2.GetWorld()->GetRightVector()));

		a = fabs(rect1Up.Dot(object2.GetWorld()->GetRightVector()))
			+ fabs(rect1Right.Dot(object2.GetWorld()->GetRightVector()));

		b = object2.GetWorld()->GetScale().x * 0.5f;

		if (c > a + b)
			return false;

		c = fabs(distance.Dot(object2.GetWorld()->GetUpVector()));

		a = fabs(rect1Up.Dot(object2.GetWorld()->GetUpVector()))
			+ fabs(rect1Right.Dot(object2.GetWorld()->GetUpVector()));

		b = object2.GetWorld()->GetScale().y * 0.5f;

		if (c > a + b)
			return false;

		return true;
	}

	bool IntersectCircleCircle(const CIRCLE& circle1, const CIRCLE& circle2)
	{
		Vector2 distance = circle1.pivot - circle2.pivot;
		if (distance.Length() < circle1.radius + circle2.radius)
			return true;

		return false;
	}

	bool IntersectRectCircle(const RECT& rect, const CIRCLE& circle)
	{
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