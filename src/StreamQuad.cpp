#include "StreamQuad.h"
#include <assert.h>
#include "ErrorHandler.h"
#include "WindowHandler.h"


void StreamQuad::Init(SDL_Renderer* aRenderer, Vector2i aSize)
{
	assert(aRenderer != nullptr);
	myRenderer = aRenderer;
	myTexture = SDL_CreateTexture(myRenderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, aSize.x, aSize.y); //Change this if we need transparency 
	PrintLastSDLError();
	assert(myTexture != nullptr);
	myDestRect.w = aSize.x;
	myDestRect.h = aSize.y;

    SetTextureColor(1,1,1);
}
void StreamQuad::SetTextureColor(float r, float g, float b)
{
	LockTexture();
	Uint32* pixels = (Uint32*)GetPixels();
	int pixelCount = GetSize().x * GetSize().y;
	auto format = WindowHandler::GetInstance()->GetPixelFormat();
	Uint32 color = SDL_MapRGB(format, r * 255, g * 255, b * 255);
	for (size_t i = 0; i < pixelCount; i++)
	{
		pixels[i] = color;
	}
    UnlockTexture();
}
void StreamQuad::Render()
{
	SDL_FPoint center;
	center.x = myCenter.x;
	center.y = myCenter.y;
	SDL_RenderCopyExF(myRenderer, myTexture, NULL, &myDestRect, myRotation, &center, SDL_FLIP_NONE); //maybe add flip options if necessary
}

Vector2f StreamQuad::GetPosition()
{
	return {myDestRect.x, myDestRect.y};
}
Vector2f StreamQuad::GetSize()
{
	return {myDestRect.w, myDestRect.h};
}
void StreamQuad::SetPosition(Vector2f aPosition)
{
	SetPosition(aPosition.x, aPosition.y);
}
void StreamQuad::SetPosition(float aX, float aY)
{
	myDestRect.x = aX;
	myDestRect.y = aY;
}
void StreamQuad::SetSize(Vector2f aSize)
{
	SetSize(aSize.x, aSize.y);
}

void StreamQuad::SetSize(float aWidth, float aHeight)
{
	myDestRect.w = aWidth;
	myDestRect.h = aHeight;
}
void StreamQuad::SetColorRGB(float r, float g, float b)
{
	int newR = (int)(r * 255.f);
	int newG = (int)(g * 255.f);
	int newB = (int)(b * 255.f);
	SDL_SetTextureColorMod(myTexture, newR, newG, newB);
}
void StreamQuad::SetRotation(float aRotation)
{
	myRotation = aRotation;
}
float StreamQuad::GetRotation()
{
	return myRotation;
}
void StreamQuad::SetCenter(Vector2f aCenter)
{
	myCenter = aCenter;
}
void StreamQuad::Reset()
{
	myRotation = 0;
	myCenter = {0,0};
	myDestRect = {0,0,0,0};
}
bool StreamQuad::LockTexture()
{
    if(myPixels != nullptr)
    {
        printf("ERROR: trying to lock already locked texture\n");
        return false;
    }
    if(SDL_LockTexture(myTexture, nullptr, &myPixels, &myPitch) != 0)
    {
        PrintLastSDLError();
        return false;
    }
    return true;
}
bool StreamQuad::UnlockTexture()
{
    if(myPixels == nullptr)
    {
        printf("ERROR: trying to unlock unlocked texture\n");
        return false;
    }
    SDL_UnlockTexture(myTexture);
    myPixels = nullptr;
    myPitch = 0;
    return true;
}

StreamQuad::~StreamQuad()
{
	SDL_DestroyTexture(myTexture);
}