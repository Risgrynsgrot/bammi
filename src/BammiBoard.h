#pragma once
#include "robin_hood.h"
#include "Grid.h"
#include "Sprite.h"
#include <vector>
#include "Text.h"

namespace Bammi
{
	struct Cell
	{
		int tileId = -1;
		bool hovered = false;
	};

	struct Tile
	{
		typedef int cellIndex;
		std::vector<cellIndex> cells;
		std::vector<Tile> neighbors;
		int fillRate = 0;
	};

	class Board
	{
	public:
		void Init(Vector2i aBoardSize, SDL_Renderer* aRenderer);
		void Update(float aDeltaTime);
		void Render();
		void RenderDebug();
	private:
		void SetupTiles();
		Grid<Cell> myGrid;
		robin_hood::unordered_map<int, Tile> myTiles;
		Sprite myRectangle;
		Text myTileIdText;
	};
}
