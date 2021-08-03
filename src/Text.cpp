#include "Text.h"

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
	myText = aText;
	myDirty = true;
}
void Text::Render()
{
	if(myDirty)
	{
		if(mySurface != nullptr)
		{
			SDL_FreeSurface(mySurface);
			SDL_DestroyTexture(myTexture);
		}
		mySurface = TTF_RenderText_Solid(myFont, myText.c_str(), myColor);
		myTexture = SDL_CreateTextureFromSurface(myRenderer, mySurface);
		Vector2i textureSize;
		SDL_QueryTexture(myTexture, NULL, NULL, &textureSize.x, &textureSize.y);
		myDestRect.w = textureSize.x;
		myDestRect.h = textureSize.y;
	}
	SDL_RenderCopyF(myRenderer, myTexture, NULL, &myDestRect);
}
void Text::SetColor(float aR, float aG, float aB)
{
	myColor.r = aR * 255.f;
	myColor.g = aG * 255.f;
	myColor.b = aB * 255.f;
	myDirty = true;
}