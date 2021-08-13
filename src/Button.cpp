#include "Button.h"

void Button::TryClick(Vector2f aClickPosition)
{
	if (IsInside(aClickPosition))
	{
		myOnClick();
	}
}

void Button::SetOnClick(std::function<void()> aFunction)
{
	myOnClick = aFunction;
}

bool Button::IsInside(Vector2f aClickPos)
{
	return myPosition.x < aClickPos.x &&
		   myPosition.x + mySize.x > aClickPos.x &&
		   myPosition.y < aClickPos.y &&
		   myPosition.y + mySize.y > aClickPos.y;
}

void Button::SetSize(Vector2f aSize)
{
	mySize = aSize;
}

void Button::SetPosition(Vector2f aPosition)
{
	myPosition = aPosition;
}