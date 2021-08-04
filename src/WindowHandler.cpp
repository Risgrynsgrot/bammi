#include "WindowHandler.h"

WindowHandler* WindowHandler::myInstance = nullptr;

void WindowHandler::SetWindow(SDL_Window* aWindow)
{
	myWindow = aWindow;
}
Vector2i WindowHandler::GetWindowSize()
{
	Vector2i result;
	SDL_GetWindowSize(myWindow, &result.x, &result.y);
	return result;
}