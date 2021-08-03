#include "Engine.h"

#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/websocket.h>
#endif
#include "WindowHandler.h"

bool Engine::Init()
{
	InitRendering();
	myGame.Init(myRenderer);

	myMousePos.Init("assets/hack.ttf", 14, myRenderer);

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
		if(myDebugMode)
		{
			UpdateDebug();
		}

		Render();
		if(myDebugMode)
		{
			RenderDebug();
		}
		SDL_RenderPresent(myRenderer);
	}
#endif

}

void Engine::InitRendering()
{
	SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	//SDL_CreateWindowAndRenderer(512, 512, 0, &window, &renderer);
	myWindow = SDL_CreateWindow("nice", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, ::SDL_WINDOW_RESIZABLE);
	myRenderer = SDL_CreateRenderer(myWindow, -1, 0);
	//myRenderTarget = SDL_CreateRGBSurface(0, 1920, 1080, 32, 0, 0, 0, 0);
	WindowHandler::GetInstance()->SetWindow(myWindow);
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

void Engine::UpdateDebug()
{
	ShowMousePos();
}

void Engine::Render()
{
	SDL_RenderClear(myRenderer);
	myGame.Render();
}
void Engine::RenderDebug()
{
	myMousePos.Render();
}

void Engine::ShowMousePos()
{
	Vector2i mousePos;
	SDL_GetMouseState(&mousePos.x, &mousePos.y);
	char buffer[64];
	sprintf(buffer, "%d, %d", mousePos.x, mousePos.y);
	myMousePos.SetText(buffer);
	myMousePos.SetPosition({mousePos.x + 16.f, mousePos.y - 16.f});
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
	//SDL_FreeSurface(myRenderTarget);
	//myRenderTarget = nullptr;
	SDL_DestroyRenderer(myRenderer);
	SDL_DestroyWindow(myWindow);
	myWindow = nullptr;
    IMG_Quit();
	TTF_Quit();
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
				switch (myEvent.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					myRunning = false; //REMOVE LATER, JUST FOR DEBUGGING
					break;
				case SDLK_F1:
					myDebugMode = true;
					break;
				case SDLK_F2:
					myDebugMode = false; //Turn into toggle later
					break;
				}
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