#pragma once
#include <SDL.h>
#include "Game.h"
#include "Text.h"

class Engine
{
public:
	bool Init();
	float GetDeltaTime();
	void Update();
	void UpdateDebug();
	void Render();
	void RenderDebug();
	void Quit();
private:
	void ShowMousePos();
	void InitMainLoop();
	void InitRendering();
	void HandleEvents();
	void SetDeltaTime();
	SDL_Renderer* myRenderer;
	SDL_Window* myWindow;
	SDL_Event myEvent;
	float myTickTime;
	float myLastTickTime;
	float myDeltaTime;
	bool myRunning;
	Game myGame;
	Text myMousePos;
	bool myDebugMode = true;
};