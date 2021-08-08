#pragma once
#include "Vector2.h"
#include "SDL.h"

class WindowHandler
{
public:
	Vector2i GetWindowSize();
	inline SDL_PixelFormat* GetPixelFormat(){return myPixelFormat;};
	void SetWindow(SDL_Window* aWindow);
	static inline WindowHandler* GetInstance()
	{
		if(myInstance == nullptr)
		{
			myInstance = new WindowHandler();
		}
		return myInstance;
	};
private:
	SDL_Window* myWindow;
	SDL_PixelFormat* myPixelFormat = nullptr;
	static WindowHandler* myInstance;
};