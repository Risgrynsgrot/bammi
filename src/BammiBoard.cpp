#include "BammiBoard.h"
#include "WindowHandler.h"
#include <stack>
#include "Primitives.h"

void Bammi::Board::Init(Vector2i aBoardSize, SDL_Renderer* aRenderer)
{
	const int cellSize = 64;
	myGrid.Init(aBoardSize, cellSize, {128.f, 128.f});
	//myRectangle.Init("assets/whitePixel.bmp", aRenderer);
	//myRectangle.SetSize({cellSize, cellSize});
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
			Color color;
			if(cell->hovered)
			{
				color = {0.7f, 0.7f, 0.7f, 1.f};
			}
			auto cellSize = myGrid.GetCellSize();
			Vector2f cellPos(x * cellSize, y * cellSize);
			cellPos += myGrid.GetPosition();
			auto& primDraw = PrimitiveDrawer::GetInstance();
			primDraw.DrawRectangle(cellPos, {cellSize, cellSize}, color);
			//myRectangle.SetPosition(cellPos);
			//myRectangle.Render();
			//myRectangle.SetColorRGB(1.f, 1.f, 1.f);

			if((cell->myBorder & (int)Border::right))
			{
				primDraw.DrawLine({cellPos.x + cellSize, cellPos.y}, {cellPos.x + cellSize, cellPos.y + cellSize}, 2.f, {1,0,1,1});
			}
			if((cell->myBorder & (int)Border::left))
			{
				primDraw.DrawLine({cellPos.x, cellPos.y}, {cellPos.x, cellPos.y + cellSize}, 2.f, {1,0,1,1});
			}
			if((cell->myBorder & (int)Border::up))
			{
				primDraw.DrawLine({cellPos.x, cellPos.y}, {cellPos.x + cellSize, cellPos.y}, 2.f, {1,0,1,1});
			}
			if((cell->myBorder & (int)Border::down))
			{
				primDraw.DrawLine({cellPos.x, cellPos.y + cellSize}, {cellPos.x + cellSize, cellPos.y + cellSize}, 2.f, {1,0,1,1});
			}


		}
	}
	for (auto& pair : myTiles)
	{
		auto& tile = pair.second;

		Cell* tileCell = myGrid.GetCellAtIndex(tile.cells[0]);

		myTileIdText.SetPosition(myGrid.GetCellPosition(tile.cells[0]));
		char buffer[64];
		sprintf(buffer, "%d / %d", tile.fillRate, (int)tile.neighbors.size());
		myTileIdText.SetText(buffer);
		myTileIdText.SetColor(0,0,0);
		myTileIdText.Render();
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


	Vector2i mousePos;
	SDL_GetMouseState(&mousePos.x, &mousePos.y);
	Vector2i windowCenter = WindowHandler::GetInstance()->GetWindowSize() / 2;
	PrimitiveDrawer::GetInstance().DrawLine({mousePos.x, mousePos.y}, {windowCenter.x, windowCenter.y},  8, {1,0,1,1});
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

	//Create Tiles
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

	//Create Borders
	for (int y = 0; y < myGrid.GetSize().y; y++)
	{
		for(int x = 0; x < myGrid.GetSize().x; x++)
		{
			Cell *cell = myGrid.GetCellAtGridPos(x, y);

			Cell *cellRight = myGrid.GetCellAtGridPos(x + 1, y);
			Cell *cellLeft = myGrid.GetCellAtGridPos(x - 1, y);
			Cell *cellUp = myGrid.GetCellAtGridPos(x, y - 1);
			Cell *cellDown = myGrid.GetCellAtGridPos(x, y + 1);

			if (cellRight != nullptr && cellRight->tileId != cell->tileId)
			{
				cell->myBorder += (int)Border::right;
				myTiles[cell->tileId].neighbors.insert(cellRight->tileId);
			}
			if (cellLeft != nullptr && cellLeft->tileId != cell->tileId)
			{
				cell->myBorder += (int)Border::left;
				myTiles[cell->tileId].neighbors.insert(cellLeft->tileId);
			}
			if (cellUp != nullptr && cellUp->tileId != cell->tileId)
			{
				cell->myBorder += (int)Border::up;
				myTiles[cell->tileId].neighbors.insert(cellUp->tileId);
			}
			if (cellDown != nullptr && cellDown->tileId != cell->tileId)
			{
				cell->myBorder += (int)Border::down;
				myTiles[cell->tileId].neighbors.insert(cellDown->tileId);
			}
		}
	}
}