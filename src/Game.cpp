#include "Game.h"
#include <assert.h>
#include "WindowHandler.h"
#include "InputHandler.h"

void Game::Init(SDL_Renderer* aRenderer)
{
	assert(aRenderer != nullptr && "renderer was nullptr in game init");
	myRenderer = aRenderer;
}

void Game::Start()
{
	mySprite.Init("assets/test.png", myRenderer);
	mySprite.SetPosition({64.f, 64.f});

	myBoard.Init({5, 5}, myRenderer, &myPlayerManager);

	myText.Init("assets/OptimusPrinceps.ttf", 48, myRenderer);
	myText.SetText("Nice");
	myText.SetPosition({512.f, 128.f});

	myPlayerManager.Init(myRenderer, &myBoard);
	myPlayerManager.AddPlayer({{1, 0, 1, 1}, "Benjamin"});
	myPlayerManager.AddPlayer({{0, 1, 0, 1}, "Lukas"});
}

void Game::Update(float aDeltaTime)
{
	myBoard.Update(aDeltaTime);
	myPlayerManager.Update();
	InputHandler& input = InputHandler::GetInstance();
	if(input.GetMouseKeyPressed(1))
	{
		auto mousePos = input.GetMousePosition();
		Bammi::Tile* tile = myBoard.GetTileAtPosition({mousePos.x, mousePos.y});
		if(tile == nullptr)
		{
			return;
		}

		Move move;
		move.player = myPlayerManager.GetCurrentPlayerIndex();
		int tileIndex = myBoard.GetTileIndexAtPosition({mousePos.x, mousePos.y});
		move.tile = tileIndex;
		if(tileIndex != -1)
		{
			if(myPlayerManager.DoMove(move))
			{
				myPlayerManager.EndTurn();
			}
		}

	}
}

void Game::Render()
{
	mySprite.Render();
	myBoard.Render();
	myText.Render();
	myPlayerManager.Render();
	//myBoard.RenderDebug();
}

void Game::Quit()
{
}