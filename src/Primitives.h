#pragma once
#include "Sprite.h"

struct Color
{
	float r = 1.f;
	float g = 1.f;
	float b = 1.f;
	float a = 1.f;
};

class PrimitiveDrawer
{
public:
	void Init(SDL_Renderer* aRenderer);
	void DrawRectangle(SDL_FRect aDstRect, Color aColor = Color());
	void DrawRectangle(float aX, float aY, float aWidth, float aHeight, Color aColor = Color());
	void DrawRectangle(Vector2f aPosition, Vector2f aSize, Color aColor = Color());
	void DrawLine(Vector2f aFrom, Vector2f aTo, float aThickness, Color aColor = Color());

	static inline PrimitiveDrawer& GetInstance()
	{
		static PrimitiveDrawer myInstance;
		return myInstance;
	};
private:
	Sprite mySprite;
};