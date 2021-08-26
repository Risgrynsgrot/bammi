#include "CollisionRect.h"

bool CollisionRect::IsInside(Vector2f aPosition)
{
	return myPosition.x < aPosition.x &&
		   myPosition.x + mySize.x > aPosition.x &&
		   myPosition.y < aPosition.y &&
		   myPosition.y + mySize.y > aPosition.y;
}