#include "Sprite.h"
#include <assert.h>
#include <iostream>
#include "ErrorHandler.h"

void Sprite::Init(const char *aFilePath, SDL_Renderer* aRenderer)
{
	assert(aRenderer != nullptr);
	myRenderer = aRenderer;
	SDL_Surface* surface = IMG_Load(aFilePath);
	PrintLastSDLError();
	myTexture = SDL_CreateTextureFromSurface(myRenderer, surface);
	assert(myTexture != nullptr);
	myDestRect.w = surface->w;
	myDestRect.h = surface->h;
	SDL_FreeSurface(surface);
}
Vector2f Sprite::GetPosition()
{
	return {myDestRect.x, myDestRect.y};
}
Vector2f Sprite::GetSize()
{
	return {myDestRect.w, myDestRect.h};
}
void Sprite::SetPosition(Vector2f aPosition)
{
	SetPosition(aPosition.x, aPosition.y);
}
void Sprite::SetPosition(float aX, float aY)
{
	myDestRect.x = aX;
	myDestRect.y = aY;
}
void Sprite::SetSize(Vector2f aSize)
{
	SetSize(aSize.x, aSize.y);
}

void Sprite::SetSize(float aWidth, float aHeight)
{
	myDestRect.w = aWidth;
	myDestRect.h = aHeight;
}

void Sprite::Render()
{
	SDL_RenderCopyF(myRenderer, myTexture, NULL, &myDestRect);
}
void Sprite::SetColorRGB(float r, float g, float b)
{
	int newR = (int)(r * 255.f);
	int newG = (int)(g * 255.f);
	int newB = (int)(b * 255.f);
	SDL_SetTextureColorMod(myTexture, newR, newG, newB);
}
Sprite::~Sprite()
{
	SDL_DestroyTexture(myTexture);
}