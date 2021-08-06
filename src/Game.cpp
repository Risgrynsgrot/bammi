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
	myBoard.Init({5, 5}, myRenderer, &myPlayerManager, 96);

	myPlayerManager.Init(myRenderer, &myBoard);
	myPlayerManager.AddPlayer({{0, 1, 0, 1}, "Benjamin"});
	myPlayerManager.AddPlayer({{0.7, 0.7, 1, 1}, "Matilda"});
}

void Game::Update(float aDeltaTime)
{
	myBoard.Update(aDeltaTime);
	myPlayerManager.Update();
	InputHandler& input = InputHandler::GetInstance();
	if(input.GetMouseKeyPressed(1))
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
			if(result.playerWon != -1)
			{
				myPlayerManager.EndGame();
			}
			else if(result.validMove)
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