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
		Text text; //change to sprite later
	};

	struct Line
	{
		Vector2f from = {0,0};
		Vector2f to = {0,0};
	};

	class Board
	{
	public:
		void Init(Vector2i aBoardSize, SDL_Renderer* aRenderer, PlayerManager* aPlayerManager, int aCellSize);
		void Update(float aDeltaTime);
		void Render();
		void RenderDebug();
		void Reset();
		bool FillTile(TileIndex aIndex, int aPlayerIndex);
		Tile* GetTileAtPosition(Vector2f aPosition);
		int GetTileIndexAtPosition(Vector2f aPosition);
		Tile* GetTileAtIndex(int aIndex);
	private:
		void DrawTiles();
		void DrawBorders();
		void DrawTileText();
		void SetupTiles(SDL_Renderer* aRenderer);
		Grid<Cell> myGrid;
		robin_hood::unordered_node_map<TileIndex, Tile> myTiles;
		Sprite myRectangle;
		PlayerManager* myPlayerManager;
		std::vector<Line> myBorders;
		SDL_Renderer* myRenderer;
	};
}
