#pragma once
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include "Vector2.h"

class Sprite
{
public:
	void Init(const char* aFilePath, SDL_Renderer* aRenderer);
	Vector2f GetPosition();
	Vector2f GetSize();
	void SetPosition(Vector2f aPosition);
	void SetSize(Vector2f aSize);
	void SetPosition(float aX, float aY);
	void SetSize(float aWidth, float aHeight);
	void Render();
	void SetColorRGB(float r, float g, float b);
	~Sprite();
private:
	SDL_Texture* myTexture = nullptr;
	//SDL_Rect mySourceRect; //maybe add later
	SDL_FRect myDestRect;
	SDL_Renderer* myRenderer;
};