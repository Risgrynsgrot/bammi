#include "Sprite.h"
#include <assert.h>
#include <iostream>
#include "ErrorHandler.h"

int Sprite::DRAWCALLS;

void Sprite::Init(const char *aFilePath, SDL_Renderer* aRenderer)
{
	assert(aRenderer != nullptr);
	myRenderer = aRenderer;
	SDL_Surface* surface = IMG_Load(aFilePath);
	if(!surface)
	{
		printf("Failed to load image in sprite: %s\n", aFilePath);
		PrintLastSDLError();
	}
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
	SDL_FPoint center;
	center.x = myCenter.x;
	center.y = myCenter.y;
	SDL_RenderCopyExF(myRenderer, myTexture, NULL, &myDestRect, myRotation, &center, SDL_FLIP_NONE); //maybe add flip options if necessary
	DRAWCALLS++;
}
void Sprite::SetColorRGB(float r, float g, float b)
{
	int newR = (int)(r * 255.f);
	int newG = (int)(g * 255.f);
	int newB = (int)(b * 255.f);
	SDL_SetTextureColorMod(myTexture, newR, newG, newB);
}
void Sprite::SetRotation(float aRotation)
{
	myRotation = aRotation;
}
float Sprite::GetRotation()
{
	return myRotation;
}
void Sprite::SetCenter(Vector2f aCenter)
{
	myCenter = aCenter;
}
void Sprite::Reset()
{
	myRotation = 0;
	myCenter = {0,0};
	myDestRect = {0,0,0,0};
}
Sprite::~Sprite()
{
	SDL_DestroyTexture(myTexture);
}