#pragma once
#include <SDL.h>
#include "Game.h"

class Engine
{
public:
	bool Init();
	float GetDeltaTime();
	void Update();
	void Quit();
private:
	void InitMainLoop();
	void InitRendering();
	void HandleEvents();
	void SetDeltaTime();
	SDL_Renderer* myRenderer;
	SDL_Window* myWindow;
	SDL_Surface* myRenderTarget;
	SDL_Event myEvent;
	float myTickTime;
	float myLastTickTime;
	float myDeltaTime;
	bool myRunning;
	Game myGame;
};