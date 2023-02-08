#include "stdafx.h"
#include "ColliderComponent.h"

bool ColliderComponent::intersect(const Vector2& coord)
{
	shared_ptr<WorldComponent> world = GetOwner()->GetWorld();
	Vector2 position = world->GetPosition();
	Vector2 scale = world->GetScale();

	if (type == ColliderType::RECT)
	{
		//rect의 중심을 기준으로 잡고 점을 상대적으로 이동하면 회전의 유무에 상관없이 충돌을 확인 할 수 있다.
		if (world->GetRightVector() == RIGHT)
		{
			Collision::RECT rect(position, scale);
			return Collision::IntersectRectCoord(rect, coord);
		}
		else
		{
			//Invert역행렬
			Matrix rectInverse = (world->GetR() * world->GetT()).Invert();
			//행렬변환 행렬을 Vector2로 변환해준다.
			Vector2 transformedCoord = Vector2::Transform(coord, rectInverse);

			Collision::RECT rect(Vector2(0.0f, 0.0f), scale);
			return Collision::IntersectRectCoord(rect, transformedCoord);
		}
	}
	else if (type == ColliderType::CIRCLE)
	{
		Collision::CIRCLE circle(position, scale);
		return Collision::IntersectCircleCoord(circle, coord);
	}
	return false;
}

bool ColliderComponent::intersect(const shared_ptr<ColliderComponent>& other)
{
	shared_ptr<WorldComponent> world = GetOwner()->GetWorld();
	shared_ptr<WorldComponent> otherWorld = other->GetOwner()->GetWorld();
	Vector2 position = world->GetPosition();
	Vector2 scale = world->GetScale();

	Vector2 otherPos = otherWorld->GetPosition();
	Vector2 otherScale = otherWorld->GetScale();

	if (type == ColliderType::RECT)
	{
		if (other->type == ColliderType::RECT)
		{
			if (world->GetRightVector() == RIGHT && otherWorld->GetRightVector() == RIGHT)
			{
				Collision::RECT rect1(position, scale);
				Collision::RECT rect2(otherPos, otherScale);
				return Collision::IntersectRectRect(rect1, rect2);
			}
			else
			{
				return Collision::IntersectRectRect(*GetOwner(), *(other->GetOwner()));
			}
		}
		else if (other->type == ColliderType::CIRCLE)
		{
			if (world->GetRightVector() == RIGHT)
			{
				Collision::RECT rect(position, scale);
				Collision::CIRCLE circle(otherPos, otherScale);

				return Collision::IntersectRectCircle(rect, circle);
			}
			else
			{
				Matrix rectInverse = (world->GetR() * world->GetT()).Invert();
				Vector2 circlePivot = Vector2::Transform(otherPos, rectInverse);

				Collision::RECT rect(Vector2(0, 0), scale);
				Collision::CIRCLE circle(circlePivot, otherScale);

				return Collision::IntersectRectCircle(rect, circle);
			}
		}
	}

	else if (type == ColliderType::CIRCLE)
	{
		if (other->type == ColliderType::RECT)
		{
			if (otherWorld->GetRightVector() == RIGHT)
			{
				Collision::CIRCLE circle(position, scale);
				Collision::RECT rect(otherPos, otherScale);

				return Collision::IntersectRectCircle(rect, circle);
			}
			else
			{
				Matrix rectInverse = (otherWorld->GetR() * otherWorld->GetT()).Invert();
				Vector2 circlePivot = Vector2::Transform(position, rectInverse);

				Collision::RECT rect(Vector2(0, 0), otherScale);
				Collision::CIRCLE circle(circlePivot, scale);

				return Collision::IntersectRectCircle(rect, circle);
			}
		}
		else if (other->type == ColliderType::CIRCLE)
		{
			Collision::CIRCLE circle1(position, scale);
			Collision::CIRCLE circle2(otherPos, otherScale);
			return Collision::IntersectCircleCircle(circle1, circle2);
		}
	}

	return false;
}
