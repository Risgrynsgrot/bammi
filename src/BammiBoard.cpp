#include "BammiBoard.h"
#include "WindowHandler.h"
#include <stack>

void Bammi::Board::Init(Vector2i aBoardSize, SDL_Renderer* aRenderer)
{
	const int cellSize = 64;
	myGrid.Init(aBoardSize, cellSize, {128.f, 128.f});
	myRectangle.Init("assets/whitePixel.bmp", aRenderer);
	myRectangle.SetSize({cellSize, cellSize});
	myTileIdText.Init("assets/hack.ttf", 14, aRenderer);
	SetupTiles();
}

void Bammi::Board::Render()
{
	auto gridSize = myGrid.GetSize();
	for (int y = 0; y < gridSize.y; y++)
	{
		for (int x = 0; x < gridSize.x; x++)
		{
			Cell* cell = myGrid.GetCellAtGridPos(x, y);
			if(cell->hovered)
			{
				myRectangle.SetColorRGB(0.7f, 0.7f, 0.7f);
			}
			Vector2f cellPos(x * myGrid.GetCellSize(), y * myGrid.GetCellSize());
			cellPos += myGrid.GetPosition();
			myRectangle.SetPosition(cellPos);
			myRectangle.Render();
			myRectangle.SetColorRGB(1.f, 1.f, 1.f);
		}
	}
}

void Bammi::Board::RenderDebug()
{
	auto gridSize = myGrid.GetSize();
	myTileIdText.SetColor(0, 0, 0);
	for (int y = 0; y < gridSize.y; y++)
	{
		for (int x = 0; x < gridSize.x; x++)
		{
			Cell* cell = myGrid.GetCellAtGridPos(x, y);
			Vector2f cellPos(x * myGrid.GetCellSize(), y * myGrid.GetCellSize());
			cellPos += myGrid.GetPosition();
			myTileIdText.SetPosition(cellPos);
			char buffer[64];
			sprintf(buffer, "%d", cell->tileId);
			myTileIdText.SetText(buffer);
			myTileIdText.Render();
		}
	}
}

void Bammi::Board::Update(float aDeltaTime)
{
	auto boardPos = WindowHandler::GetInstance()->GetWindowSize();
	boardPos /= 2;
	auto size = myGrid.GetSize() * myGrid.GetCellSize();
	boardPos -= size / 2;

	myGrid.SetPosition({boardPos.x, boardPos.y});

	//Reset hover
	auto gridSize = myGrid.GetSize();
	for (int y = 0; y < gridSize.y; y++)
	{
		for (int x = 0; x < gridSize.x; x++)
		{
			Cell* cell = myGrid.GetCellAtGridPos(x, y);
			cell->hovered = false;
		}
	}

	//Set hovered
	Vector2i mousePos;
	SDL_GetMouseState(&mousePos.x, &mousePos.y);
	Cell *cell = myGrid.GetCellAtPosition(mousePos.x, mousePos.y);
	if (cell != nullptr)
	{
			auto& hoveredCells = myTiles[cell->tileId].cells;
			for (size_t i = 0; i < hoveredCells.size(); i++)
			{
				myGrid.GetCellAtIndex(hoveredCells[i])->hovered = true;
			}
	}
}

void Bammi::Board::SetupTiles()
{
	//Some kind of random flood fill

	std::stack<int> myCellsToAssign;
	int currentTileId = 0;
	int currentCellOrigin = 0;
	int cellCount = myGrid.GetSize().x * myGrid.GetSize().y;
	bool placedTile = false;

	for (size_t i = 0; i < cellCount; i++)
	{
		myCellsToAssign.push(i);
		while (!myCellsToAssign.empty())
		{
			int cellIndex = myCellsToAssign.top();
			Cell *cell = myGrid.GetCellAtIndex(cellIndex);
			myCellsToAssign.pop();

			if (cellIndex > cellCount - 1 || cellIndex < 0)
			{
				continue;
			}

			if (cell->tileId == -1)
			{
				if(!placedTile)
				{
					myTiles[currentTileId] = Tile();
				}

				auto &tile = myTiles[currentTileId];
				tile.cells.push_back(cellIndex);

				cell->tileId = currentTileId;
				placedTile = true;
				int cellX = cellIndex % myGrid.GetSize().x;
				int cellY = cellIndex / myGrid.GetSize().x;

				if(cellX + 1 < myGrid.GetSize().x)
				{
					if (rand() % 3 == 0)
					{
						myCellsToAssign.push(cellIndex + 1);
					}
				}
				if(cellX - 1 >= 0)
				{
					if (rand() % 3 == 0)
					{
						myCellsToAssign.push(cellIndex - 1);
					}
				}
				if(cellY + 1 < myGrid.GetSize().y)
				{
					if (rand() % 3 == 0)
					{
						myCellsToAssign.push(cellIndex + myGrid.GetSize().x);
					}
				}
				if(cellY - 1 >= 0)
				{
					if (rand() % 3 == 0)
					{
						myCellsToAssign.push(cellIndex - myGrid.GetSize().x);
					}
				}
			}
		}
		if (placedTile)
		{
			currentTileId++;
			placedTile = false;
		}
	}
}