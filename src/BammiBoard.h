#pragma once
#include "robin_hood.h"
#include "Grid.h"
#include "Sprite.h"
#include <vector>
#include "Text.h"

class PlayerManager;

namespace Bammi
{
	typedef int TileIndex;
	typedef int CellIndex;
	enum struct Border
	{
		right = 1 << 0,
		up = 	1 << 1,
		left = 	1 << 2,
		down = 	1 << 3
	};
	struct Cell
	{
		TileIndex tileId = -1;
		bool hovered = false;
		int myBorder = 0;
	};

	struct Tile
	{
		std::vector<CellIndex> cells;
		robin_hood::unordered_set<TileIndex> neighbors;
		int fillRate = 0;
		int playerIndex = -1;
	};

	class Board
	{
	public:
		void Init(Vector2i aBoardSize, SDL_Renderer* aRenderer, PlayerManager* aPlayerManager);
		void Update(float aDeltaTime);
		void Render();
		void RenderDebug();
		void FillTile(TileIndex aIndex, int aPlayerIndex);
		Tile* GetTileAtPosition(Vector2f aPosition);
		int GetTileIndexAtPosition(Vector2f aPosition);
		Tile* GetTileAtIndex(int aIndex);
	private:
		void SetupTiles();
		Grid<Cell> myGrid;
		robin_hood::unordered_map<TileIndex, Tile> myTiles;
		Sprite myRectangle;
		Text myTileIdText;
		PlayerManager* myPlayerManager;
	};
}
