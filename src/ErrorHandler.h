#pragma once
#include <SDL.h>
#include <stdio.h>

inline void PrintLastSDLError()
{
	char error[512];
	SDL_GetErrorMsg(error, 512);
	printf("%s\n", error);
}