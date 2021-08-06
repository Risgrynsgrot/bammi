#include "Engine.h"

#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/websocket.h>
#endif
#include "WindowHandler.h"
#include "Primitives.h"
#include "InputHandler.h"

bool Engine::Init()
{
	InitRendering();
	myGame.Init(myRenderer);

	myMousePos.Init("assets/hack.ttf", 14, myRenderer);
	myFramerate.Init("assets/hack.ttf", 14, myRenderer);

	PrimitiveDrawer::GetInstance().Init(myRenderer);

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

		Sprite::DRAWCALLS = 0;

		Render();
		//printf("%d", Sprite::DRAWCALLS);
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
	SDL_DisplayMode dm;
	SDL_GetCurrentDisplayMode(0, &dm);
	auto width = dm.w;
	auto height = dm.h;
	width /= 1.5f;
	height /= 1.5f;
	myWindow = SDL_CreateWindow("Bammi 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, ::SDL_WINDOW_RESIZABLE);
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
	auto& inputHandler = InputHandler::GetInstance();

	if(inputHandler.GetKeyPressed(SDLK_ESCAPE))
	{
		myRunning = false; //REMOVE LATER, JUST FOR DEBUGGING
	}
	if(inputHandler.GetKeyPressed(SDLK_F2))
	{
		myDebugMode = !myDebugMode;
		printf("f2 pressed");
	}

	inputHandler.UpdateState();
}

void Engine::UpdateDebug()
{
	ShowMousePos();
	ShowFramerate();
}

void Engine::Render()
{        
	SDL_SetRenderDrawColor(myRenderer, 41, 40, 40, 255);
	SDL_RenderClear(myRenderer);
	myGame.Render();
}
void Engine::RenderDebug()
{
	PrimitiveDrawer::GetInstance().DrawRectangle(32.f, 32.f, 500, 16, {0, 0, 0, 1});
	myMousePos.Render(true);
	myFramerate.Render(true);
}

void Engine::ShowFramerate()
{
	char buffer[128];
	sprintf(buffer, "Frametime: %f ms Drawcalls: %d", myDeltaTime * 1000.f, Sprite::DRAWCALLS);
	myFramerate.SetText(buffer);
	myFramerate.SetPosition({32, 32});
}

void Engine::ShowMousePos()
{
	auto mousePos = InputHandler::GetInstance().GetMousePosition();
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
	while (SDL_PollEvent(&myEvent))
	{
		if (InputHandler::GetInstance().UpdateEvents(myEvent))
		{
			continue;
		}
		switch (myEvent.type)
		{
		case SDL_QUIT:
			myRunning = false;
			break;
		}
	}
}