#include "WindowHandler.h"

WindowHandler* WindowHandler::myInstance = nullptr;

void WindowHandler::SetWindow(SDL_Window* aWindow)
{
	myWindow = aWindow;
	if(myPixelFormat != nullptr)
	{
		SDL_FreeFormat(myPixelFormat);
	}
	Uint32 format = SDL_GetWindowPixelFormat(myWindow);
	myPixelFormat = SDL_AllocFormat(format);
}
Vector2i WindowHandler::GetWindowSize()
{
	Vector2i result;
	SDL_GetWindowSize(myWindow, &result.x, &result.y);
	return result;
}