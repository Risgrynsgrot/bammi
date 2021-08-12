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
	myBoard.Init({4, 4}, myRenderer, &myPlayerManager, 96);

	myPlayerManager.Init(myRenderer, &myBoard);
	myPlayerManager.AddPlayer({{1, 1, 0, 1}, "Benjamin"});
	//myPlayerManager.AddPlayer({{0.7, 0.7, 1, 1}, "Matilda"});
	//myPlayerManager.AddPlayer({{0, 1, 0, 1}, "Alve"});
	//myPlayerManager.AddPlayer({{1, 0, 0, 1}, "Kirsi"});
	//myPlayerManager.AddPlayer({{0, 0, 0.3, 1}, "Rickard"});
}

void Game::Update(float aDeltaTime)
{
	myBoard.Update(aDeltaTime);
	myPlayerManager.Update();
	InputHandler& input = InputHandler::GetInstance();
	if(input.GetMouseKeyPressed(1) && myBoard.ReadyToPlay())
	{
		auto mousePos = input.GetMousePosition();
		Bammi::Tile* tile = myBoard.GetTileAtPosition({(float)mousePos.x, (float)mousePos.y});
		if(tile == nullptr)
		{
			return;
		}

		Move move;
		move.player = myPlayerManager.GetCurrentPlayerIndex();
		int tileIndex = myBoard.GetTileIndexAtPosition({(float)mousePos.x, (float)mousePos.y});
		move.tile = tileIndex;
		if(tileIndex != -1 && !myPlayerManager.GameEnded())
		{
			MoveResult result = myPlayerManager.DoMove(move);
			if(result.validMove)
			{
				myPlayerManager.EndTurn();
			}
		}
		

	}
	if(input.GetKeyPressed(SDLK_r))
	{
		myBoard.Reset();
		myPlayerManager.Reset();
	}
	for (size_t i = 0; i < myPlayerManager.GetPlayerCount(); i++)
	{
		auto &player = myPlayerManager.GetPlayer(i);
		if (player.myTileCount >= myBoard.GetTileCount())
		{
			myPlayerManager.EndGame(i);
		}
	}
}

void Game::Render()
{
	myBoard.Render();
	myPlayerManager.Render();
	//myBoard.RenderDebug();
}

void Game::Quit()
{
}