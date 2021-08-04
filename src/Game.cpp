#include "Game.h"
#include <assert.h>

void Game::Init(SDL_Renderer* aRenderer)
{
	assert(aRenderer != nullptr && "renderer was nullptr in game init");
	myRenderer = aRenderer;
}

void Game::Start()
{
	mySprite.Init("assets/test.png", myRenderer);
	mySprite.SetPosition({64.f, 64.f});

	myBoard.Init({5, 5}, myRenderer);

	myText.Init("assets/OptimusPrinceps.ttf", 48, myRenderer);
	myText.SetText("Nice");
	myText.SetPosition({512.f, 128.f});
}

void Game::Update(float aDeltaTime)
{
	myBoard.Update(aDeltaTime);
}

void Game::Render()
{
	mySprite.Render();
	myBoard.Render();
	myText.Render();
	//myBoard.RenderDebug();
}

void Game::Quit()
{
}