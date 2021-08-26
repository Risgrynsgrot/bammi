#pragma once
#include <string>
#include <SDL_ttf.h>
#include "Vector2.h"

struct SDL_Renderer;

enum struct TextAlignment
{
	Left,
	Right,
	Center
};

enum struct TextOrigin
{
	Top,
	Mid,
	Bottom
};

class Text
{
public:
	void Init(const char* aFontPath, unsigned int aFontSize, SDL_Renderer* aRenderer);
	void SetPosition(Vector2f aPosition);
	void SetText(const char* aText);
	void SetColor(float aR, float aG, float aB);
	void Render(bool aFast, TextAlignment aAlignment = TextAlignment::Left, TextOrigin aOrigin = TextOrigin::Top);
	void Destroy();
	Vector2f GetSize() {return Vector2f(myDestRect.w, myDestRect.h);};
	Vector2f GetPosition() {return Vector2f(myDestRect.x, myDestRect.y);};
private:
	std::string myText = " ";
	TTF_Font* myFont = nullptr;
	SDL_Surface* mySurface = nullptr;
	SDL_Texture* myTexture = nullptr;
	SDL_Color myColor = {255, 255, 255};
	SDL_Renderer* myRenderer;
	SDL_Rect myDestRect;
	bool myDirty = true;
};