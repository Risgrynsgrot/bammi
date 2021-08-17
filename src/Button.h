#pragma once
#include <functional>
#include "Vector2.h"
#include "Text.h"
#include "Sprite.h"

class Button
{
public:
	void TryClick(Vector2f aClickPosition);
	void SetOnClick(std::function<void()> aFunction);
	void SetSize(Vector2f aSize);
	void SetPosition(Vector2f aPosition);
private:
	bool IsInside(Vector2f aClickPosition);
	Vector2f myPosition;
	Vector2f mySize;
	std::function<void()> myOnClick;
	Text myText;
	Sprite mySprite;
};