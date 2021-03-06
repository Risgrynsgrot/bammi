#pragma once
#include <functional>
#include "Vector2.h"
#include "Text.h"
#include "Sprite.h"
#include "CollisionRect.h"

class Button
{
public:
	void Init(const char* aSpritePath, SDL_Renderer* aRenderer);
	void TryClick(Vector2f aClickPosition);
	void TryHover(Vector2f aMousePosition);
	void SetOnClick(std::function<void()> aFunction);
	void SetSize(Vector2f aSize);
	void SetPosition(Vector2f aPosition);
	void SetText(const char* aText);
	void Render();
	void SetActive(bool aActive);
	inline bool GetIsActive(){return myIsActive;};
private:
	CollisionRect myRect;
	std::function<void()> myOnClick;
	Text myText;
	Sprite mySprite;
	bool myIsActive = true;
};