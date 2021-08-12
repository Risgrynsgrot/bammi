#pragma once
#include "robin_hood.h"
#include "Grid.h"
#include "Sprite.h"
#include <vector>
#include "Text.h"
#include "StreamQuad.h"
#include "SpreadEffect.h"
#include <queue>

class PlayerManager;

namespace Bammi
{
	typedef int TileIndex;
	typedef int CellIndex;
	struct Move
	{
		TileIndex aIndex;
		int aPlayerIndex;
		bool aIsExplode;
		int aSpreadAmount = 0;
	};
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
		//bool FillTile(TileIndex aIndex, int aPlayerIndex);
		void AddToTileQueue(TileIndex aIndex, int aPlayerIndex, bool aIsExplode, bool aFirst = false, int aSpreadAmount = 0);
		bool FillTile2(TileIndex aIndex, int aPlayerIndex, bool aIsExplode);
		Tile* GetTileAtPosition(Vector2f aPosition);
		int GetTileIndexAtPosition(Vector2f aPosition);
		Tile* GetTileAtIndex(int aIndex);
		inline int GetTileCount() {return myTiles.size();};
		inline bool ReadyToPlay(){return myUnHandledMoves.empty();};
	private:
		void HandleExplodingTile();
		void DrawTiles();
		void DrawBorders();
		void DrawTileText();
		void StartTileSpread(int aTileIndex, bool aShouldReset, bool aReverse);
		void UpdateTileFill(int aTileIndex);
		void SetupTiles(SDL_Renderer* aRenderer);
		Grid<Cell> myGrid;
		robin_hood::unordered_node_map<TileIndex, Tile> myTiles;
		//Sprite myRectangle;
		StreamQuad* myCellSprites;
		SpreadEffect* mySpreadEffects;
		PlayerManager* myPlayerManager;
		std::vector<Line> myBorders;
		SDL_Renderer* myRenderer;
		std::vector<Move> myUnHandledMoves;
		std::queue<TileIndex> myExplodingTiles;
	};
}
