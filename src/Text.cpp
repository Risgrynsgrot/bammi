#include "Text.h"
#include "Sprite.h"
#include <assert.h>

void Text::Init(const char* aFontPath, unsigned int aFontSize, SDL_Renderer* aRenderer)
{
	myFont = TTF_OpenFont(aFontPath, aFontSize);
	myRenderer = aRenderer;
}
void Text::SetPosition(Vector2f aPosition)
{
	myDestRect.x = aPosition.x;
	myDestRect.y = aPosition.y;
	//myDirty = true;
}
void Text::SetText(const char* aText)
{
	if(strcmp(aText, myText.c_str()) == 0)
	{
		return;
	}
	myText = aText;
	myDirty = true;
	if(myText.empty())
	{
		myDestRect.w = 0;
		myDirty = false;
	}
}
void Text::Destroy()
{
	SDL_DestroyTexture(myTexture);
	SDL_FreeSurface(mySurface);
	TTF_CloseFont(myFont);
}
void Text::Render(bool aFast, TextAlignment aAlignment, TextOrigin aOrigin)
{
	if(myText.empty())
	{
		return;
	}
	if(myDirty)
	{
		if(mySurface != nullptr)
		{
			SDL_DestroyTexture(myTexture);
			myTexture = nullptr;
			SDL_FreeSurface(mySurface);
			mySurface = nullptr;
		}
		if(aFast)
		{
			mySurface = TTF_RenderText_Solid(myFont, myText.c_str(), myColor);
			assert(mySurface != nullptr);
		}
		else
		{
			mySurface = TTF_RenderText_Blended(myFont, myText.c_str(), myColor);
			assert(mySurface != nullptr);
			//printf("dirty slow\n");
		}
		myTexture = SDL_CreateTextureFromSurface(myRenderer, mySurface);
		Vector2i textureSize;
		SDL_QueryTexture(myTexture, NULL, NULL, &textureSize.x, &textureSize.y);
		myDestRect.w = textureSize.x;
		myDestRect.h = textureSize.y;
		myDirty = false;
	}
	SDL_Rect rect = myDestRect;
	if (aAlignment == TextAlignment::Center)
	{
		rect.x -= (float)mySurface->w / 2;
	}
	if (aAlignment == TextAlignment::Right)
	{
		rect.x -= (float)mySurface->w;
	}
	if(aOrigin == TextOrigin::Mid)
	{
		rect.y -= (float)mySurface->h / 2;
	}
	if(aOrigin == TextOrigin::Bottom)
	{
		rect.y -= (float)mySurface->h;
	}
	SDL_RenderCopy(myRenderer, myTexture, NULL, &rect);
	Sprite::DRAWCALLS++;
}
void Text::SetColor(float aR, float aG, float aB)
{
	SDL_Color color = {(Uint8)(aR * 255.f), (Uint8)(aG * 255.f), (Uint8)(aB * 255.f), 1};
	if (color.r == myColor.r && color.g == myColor.g && color.b == myColor.b)
	{
		return;
	}
	myColor.r = aR * 255.f;
	myColor.g = aG * 255.f;
	myColor.b = aB * 255.f;
	myDirty = true;
}