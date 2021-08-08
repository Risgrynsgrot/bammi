#pragma once
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include "Vector2.h"

class StreamQuad
{
	friend class PrimitiveDrawer;
public:
	void Init(SDL_Renderer* aRenderer, Vector2i aSize);
	Vector2f GetPosition();
	Vector2f GetSize();
	void SetCenter(Vector2f aCenter);
	float GetRotation();
	void SetPosition(Vector2f aPosition);
	void SetSize(Vector2f aSize);
	void SetPosition(float aX, float aY);
	void SetSize(float aWidth, float aHeight);
	void Render();
	void SetColorRGB(float r, float g, float b);
	void SetRotation(float aRotation);
	void Reset();
    bool LockTexture();
    bool UnlockTexture();
	void SetTextureColor(float r, float g, float b);
    inline void* GetPixels() {return myPixels;};
    inline int GetPitch() {return myPitch;};
	~StreamQuad();
private:
	SDL_Texture* myTexture = nullptr;
	//SDL_Rect mySourceRect; //maybe add later
	SDL_FRect myDestRect;
	SDL_Renderer* myRenderer;
	float myRotation;
	Vector2f myCenter;

    void* myPixels = nullptr;
    int myPitch = 0;
};