#pragma once

class Object;

namespace Collision
{
	struct RECT
	{
		RECT(Vector2 position, Vector2 scale);

		Vector2 min;
		Vector2 max;
	};

	struct	CIRCLE
	{
		CIRCLE(Vector2 position, Vector2 scale);

		Vector2 pivot;
		float radius = 0.0f;
	};

	bool IntersectRectCoord(const RECT& rect, const Vector2& coord);
	bool IntersectCircleCoord(const CIRCLE& circle, const Vector2& coord);

	bool IntersectRectRect(const RECT& rect1, const RECT& rect2);
	bool IntersectRectRect(const Object& object1, const Object& object2);

	bool IntersectCircleCircle(const CIRCLE& circle1, const CIRCLE& circle2);

	bool IntersectRectCircle(const RECT& rect, const CIRCLE& circle);
}