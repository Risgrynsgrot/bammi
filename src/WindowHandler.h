#pragma once
#include "Vector2.h"
#include "SDL.h"

class WindowHandler
{
public:
	Vector2i GetWindowSize();
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
	static WindowHandler* myInstance;
};