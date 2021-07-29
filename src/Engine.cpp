#include "Engine.h"

#include <SDL.h>
#include <SDL2/SDL_image.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/websocket.h>
#endif

bool Engine::Init()
{
	InitRendering();
	InitMainLoop();
	Quit();
	return true;
}
void Engine::InitMainLoop()
{
	myRunning = true;

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(Update, 0, 1);
#else
	myGame.Start();
	while (myRunning)
	{
		Update();
	}
#endif

}

void Engine::InitRendering()
{
	SDL_Init(SDL_INIT_VIDEO);
	//SDL_CreateWindowAndRenderer(512, 512, 0, &window, &renderer);
	myWindow = SDL_CreateWindow("nice", 0, 0, 512, 512, ::SDL_WINDOW_RESIZABLE);
	myRenderer = SDL_CreateRenderer(myWindow, -1, 0);
	myRenderTarget = SDL_CreateRGBSurface(0, 512, 512, 32, 0, 0, 0, 0);
}

float Engine::GetDeltaTime()
{
	return myDeltaTime;
}

void Engine::Update()
{
	SetDeltaTime();
	HandleEvents();
	myGame.Update(myDeltaTime);
}

void Engine::SetDeltaTime()
{
	myLastTickTime = myTickTime;
	myTickTime = SDL_GetTicks() / 1000.f;
	myDeltaTime = myTickTime - myLastTickTime;
}

void Engine::Quit()
{
	//Release all objects
	SDL_FreeSurface(myRenderTarget);
	myRenderTarget = nullptr;
	SDL_DestroyWindow(myWindow);
	myWindow = nullptr;
	SDL_Quit();
}

void Engine::HandleEvents()
{
	while(SDL_PollEvent(&myEvent))
	{
		switch(myEvent.type)
		{
			case SDL_QUIT:
			myRunning = false;
			break;
			case SDL_KEYDOWN:
			break;
			case SDL_KEYUP:
			break;
			case SDL_MOUSEBUTTONDOWN:
			break;
			case SDL_MOUSEBUTTONUP:
			break;
		}
	}
}