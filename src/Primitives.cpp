#include "Primitives.h"
#include "Math.h"

void PrimitiveDrawer::Init(SDL_Renderer* aRenderer)
{
	mySprite.Init("assets/whitePixel.png", aRenderer);
}
void PrimitiveDrawer::DrawRectangle(SDL_FRect aDstRect, Color aColor)
{
	mySprite.SetColorRGB(aColor.r, aColor.g, aColor.b);

	mySprite.myDestRect = aDstRect;
	mySprite.Render();
	mySprite.Reset();
}
void PrimitiveDrawer::DrawRectangle(float aX, float aY, float aWidth, float aHeight, Color aColor)
{
	SDL_FRect rect;
	rect.x = aX;
	rect.y = aY;
	rect.w = aWidth;
	rect.h = aHeight;
	DrawRectangle(rect, aColor);
}
void PrimitiveDrawer::DrawRectangle(Vector2f aPosition, Vector2f aSize, Color aColor)
{
	SDL_FRect rect;
	rect.x = aPosition.x;
	rect.y = aPosition.y;
	rect.w = aSize.x;
	rect.h = aSize.y;
	DrawRectangle(rect, aColor);
}
void PrimitiveDrawer::DrawLine(Vector2f aFrom, Vector2f aTo, float aThickness, Color aColor)
{
	Vector2f diff = aTo - aFrom;
	float length = diff.Length();
	//diff.Normalize();

	float angle = atan2f(diff.y, diff.x);
	angle = Math::radToDeg(angle);
	angle -= 90.f;

	SDL_FRect rect;
	rect.x = aFrom.x;
	rect.y = aFrom.y;
	rect.w = aThickness;
	rect.h = length;

	Vector2f origin;
	origin.x = rect.w / 2;
	origin.y = 0;

	mySprite.SetCenter(origin);
	mySprite.SetRotation(angle);
	mySprite.SetColorRGB(aColor.r, aColor.g, aColor.b);
	mySprite.myDestRect = rect;

	mySprite.Render();
	mySprite.Reset();
}