#pragma once
#include <string>
#include <SDL_ttf.h>
#include "Vector2.h"

struct SDL_Renderer;

class Text
{
public:
	void Init(const char* aFontPath, unsigned int aFontSize, SDL_Renderer* aRenderer);
	void SetPosition(Vector2f aPosition);
	void SetText(const char* aText);
	void SetColor(float aR, float aG, float aB);
	void Render(bool aFast);
	void Destroy();
private:
	std::string myText = "";
	TTF_Font* myFont = nullptr;
	SDL_Surface* mySurface = nullptr;
	SDL_Texture* myTexture = nullptr;
	SDL_Color myColor = {255, 255, 255};
	SDL_Renderer* myRenderer;
	SDL_FRect myDestRect;
	bool myDirty = true;
};