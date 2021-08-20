#include "Button.h"

void Button::Init(const char* aSpritePath, SDL_Renderer* aRenderer)
{
	mySprite.Init(aSpritePath, aRenderer);
	myText.Init("assets/hack.ttf", 24, aRenderer);
	myText.SetColor(0,0,0);
}

void Button::TryHover(Vector2f aMousePosition)
{
	if (IsInside(aMousePosition))
	{
		mySprite.SetColorRGB(0.5, 0.5, 0.5);
		return;
	}
	mySprite.SetColorRGB(1,1,1);
}
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

void Button::Render()
{
	myText.SetPosition(myPosition + mySize / 2.f);
	mySprite.SetSize(mySize);
	mySprite.SetPosition(myPosition);

	mySprite.Render();
	myText.Render(false, TextAlignment::Center, TextOrigin::Mid);
}

void Button::SetPosition(Vector2f aPosition)
{
	myPosition = aPosition;
}
void Button::SetText(const char* aText)
{
	myText.SetText(aText);
}

void Button::SetActive(bool aActive)
{
	myIsActive = aActive;
}