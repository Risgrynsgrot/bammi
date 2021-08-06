#include "BammiBoard.h"
#include "WindowHandler.h"
#include <stack>
#include "Primitives.h"
#include "InputHandler.h"
#include "PlayerManager.h"

void Bammi::Board::Init(Vector2i aBoardSize, SDL_Renderer* aRenderer, PlayerManager* aPlayerManager, int aCellSize)
{
	myPlayerManager = aPlayerManager;
	myGrid.Init(aBoardSize, aCellSize, {128.f, 128.f});
	//myRectangle.Init("assets/whitePixel.bmp", aRenderer);
	//myRectangle.SetSize({cellSize, cellSize});
	myRenderer = aRenderer;
	SetupTiles(aRenderer);
}

void Bammi::Board::Render()
{
	DrawTiles();
	DrawBorders();
	
	DrawTileText();
	
}
void Bammi::Board::DrawTiles()
{
	auto gridSize = myGrid.GetSize();
	auto& primDraw = PrimitiveDrawer::GetInstance();

	for (int y = 0; y < gridSize.y; y++)
	{
		for (int x = 0; x < gridSize.x; x++)
		{
			Cell* cell = myGrid.GetCellAtGridPos(x, y);
			auto playerOwned = myTiles[cell->tileId].playerIndex;
			Color color = playerOwned != -1 ? myPlayerManager->GetPlayer(playerOwned).myColor : Color();
			if(cell->hovered)
			{
				color.r *= 0.7f;
				color.g *= 0.7f;
				color.b *= 0.7f;
			}
			auto cellSize = myGrid.GetCellSize();
			Vector2f cellPos(x * cellSize, y * cellSize);
			cellPos += myGrid.GetPosition();
			primDraw.DrawRectangle(cellPos, {(float)cellSize, (float)cellSize}, color);
			//myRectangle.SetPosition(cellPos);
			//myRectangle.Render();
			//myRectangle.SetColorRGB(1.f, 1.f, 1.f);

			//if((cell->myBorder & (int)Border::right))
			//{
			//	primDraw.DrawLine({cellPos.x + cellSize, cellPos.y}, {cellPos.x + cellSize, cellPos.y + cellSize}, 2.f, {1,0,1,1});
			//}
			//if((cell->myBorder & (int)Border::left))
			//{
			//	primDraw.DrawLine({cellPos.x, cellPos.y}, {cellPos.x, cellPos.y + cellSize}, 2.f, {1,0,1,1});
			//}
			//if((cell->myBorder & (int)Border::up))
			//{
			//	primDraw.DrawLine({cellPos.x, cellPos.y}, {cellPos.x + cellSize, cellPos.y}, 2.f, {1,0,1,1});
			//}
			//if((cell->myBorder & (int)Border::down))
			//{
			//	primDraw.DrawLine({cellPos.x, cellPos.y + cellSize}, {cellPos.x + cellSize, cellPos.y + cellSize}, 2.f, {1,0,1,1});
			//}


		}
	}
}
void Bammi::Board::DrawTileText()
{
	for (auto& pair : myTiles)
	{
		auto& tile = pair.second;

		Cell* tileCell = myGrid.GetCellAtIndex(tile.cells[0]);

		tile.text.SetPosition(myGrid.GetCellPosition(tile.cells[0]));
		char buffer[64];
		sprintf(buffer, "%d / %d", tile.fillRate, (int)tile.neighbors.size());
		tile.text.SetText(buffer);
		tile.text.SetColor(0.f,0.f,0.f);
		tile.text.Render(false); //REALLY SLOW, TEXT IS NO GOOD HAHAHA
	}
}
void Bammi::Board::DrawBorders()
{
	auto gridSize = myGrid.GetSize();
	auto& primDraw = PrimitiveDrawer::GetInstance();
	for (size_t i = 0; i < myBorders.size(); i++)
	{
		Line& line = myBorders[i];

		primDraw.DrawLine(line.from + myGrid.GetPosition(), line.to + myGrid.GetPosition(), 2.f, {0,0,0,1});
	}
}

void Bammi::Board::RenderDebug()
{
	auto gridSize = myGrid.GetSize();
//	myTileIdText.SetColor(0, 0, 0);
//	for (int y = 0; y < gridSize.y; y++)
//	{
//		for (int x = 0; x < gridSize.x; x++)
//		{
//			Cell* cell = myGrid.GetCellAtGridPos(x, y);
//			Vector2f cellPos(x * myGrid.GetCellSize(), y * myGrid.GetCellSize());
//			cellPos += myGrid.GetPosition();
//			myTileIdText.SetPosition(cellPos);
//			char buffer[64];
//			sprintf(buffer, "%d", cell->tileId);
//			myTileIdText.SetText(buffer);
//			myTileIdText.Render();
//		}
//	}


	Vector2i mousePos;
	SDL_GetMouseState(&mousePos.x, &mousePos.y);
	Vector2i windowCenter = WindowHandler::GetInstance()->GetWindowSize() / 2;
	PrimitiveDrawer::GetInstance().DrawLine({(float)mousePos.x, (float)mousePos.y}, {(float)windowCenter.x, (float)windowCenter.y},  8, {1,0,1,1});
}
void Bammi::Board::Reset()
{
	myGrid.Clear(Bammi::Cell());
	SetupTiles(myRenderer);
}

void Bammi::Board::Update(float aDeltaTime)
{
	auto boardPos = WindowHandler::GetInstance()->GetWindowSize();
	boardPos /= 2;
	auto size = myGrid.GetSize() * myGrid.GetCellSize();
	boardPos -= size / 2;

	myGrid.SetPosition({(float)boardPos.x, (float)boardPos.y});

	//Reset hover
	auto gridSize = myGrid.GetSize();
	for (int y = 0; y < gridSize.y; y++)
	{
		for (int x = 0; x < gridSize.x; x++)
		{
			Cell *cell = myGrid.GetCellAtGridPos(x, y);
			cell->hovered = false;
		}
	}

	//Set hovered
	Vector2i mousePos = InputHandler::GetInstance().GetMousePosition();
	Cell *cell = myGrid.GetCellAtPosition(mousePos.x, mousePos.y);
	if (cell != nullptr)
	{
		auto &hoveredCells = myTiles[cell->tileId].cells;
		for (size_t i = 0; i < hoveredCells.size(); i++)
		{
			myGrid.GetCellAtIndex(hoveredCells[i])->hovered = true;
		}
	}
}

void Bammi::Board::SetupTiles(SDL_Renderer* aRenderer)
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
				if (!placedTile)
				{
					myTiles[currentTileId] = Tile();
					myTiles[currentTileId].text.Init("assets/hack.ttf", 14, aRenderer);
				}

				auto &tile = myTiles[currentTileId];
				tile.cells.push_back(cellIndex);

				cell->tileId = currentTileId;
				placedTile = true;
				int cellX = cellIndex % myGrid.GetSize().x;
				int cellY = cellIndex / myGrid.GetSize().x;

				if (cellX + 1 < myGrid.GetSize().x)
				{
					if (rand() % 3 == 0)
					{
						myCellsToAssign.push(cellIndex + 1);
					}
				}
				if (cellX - 1 >= 0)
				{
					if (rand() % 3 == 0)
					{
						myCellsToAssign.push(cellIndex - 1);
					}
				}
				if (cellY + 1 < myGrid.GetSize().y)
				{
					if (rand() % 3 == 0)
					{
						myCellsToAssign.push(cellIndex + myGrid.GetSize().x);
					}
				}
				if (cellY - 1 >= 0)
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
		for (int x = 0; x < myGrid.GetSize().x; x++)
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

	for (int y = 0; y < myGrid.GetSize().y; y++)
	{
		myBorders.push_back(Line());
		auto line = &myBorders.back();
		line->from = {0.f, (float)((y + 1) * myGrid.GetCellSize())};
		line->to = line->from;
		for (int x = 0; x < myGrid.GetSize().x; x++)
		{
			Cell *cell = myGrid.GetCellAtGridPos(x, y);
			if(cell->myBorder & (int)Border::down)
			{
				line->to.x += myGrid.GetCellSize();
				continue;
			}

			if(line->to.x != line->from.x)
			{
				myBorders.push_back(Line());
				line = &myBorders.back();
			}
			line->from = {(float)((x + 1) * myGrid.GetCellSize()), (float)((y + 1) * myGrid.GetCellSize())};
			line->to = line->from;
		}
	}

	for (int x = 0; x < myGrid.GetSize().x; x++)
	{
		myBorders.push_back(Line());
		auto line = &myBorders.back();
		line->from = {(float)((x + 1) * myGrid.GetCellSize()), 0.f};
		line->to = line->from;
		for (int y = 0; y < myGrid.GetSize().y; y++)
		{
			Cell *cell = myGrid.GetCellAtGridPos(x, y);
			if(cell->myBorder & (int)Border::right)
			{
				line->to.y += myGrid.GetCellSize();
				continue;
			}

			if(line->to.y != line->from.y)
			{
				myBorders.push_back(Line());
				line = &myBorders.back();
			}
			line->from = {(float)((x + 1) * myGrid.GetCellSize()), (float)((y + 1) * myGrid.GetCellSize())};
			line->to = line->from;
		}
	}
}
Bammi::Tile *Bammi::Board::GetTileAtPosition(Vector2f aPosition)
{
	Cell *cell = myGrid.GetCellAtPosition(aPosition);
	if (cell == nullptr)
	{
		return nullptr;
	}

	return &myTiles[cell->tileId];
}
int Bammi::Board::GetTileIndexAtPosition(Vector2f aPosition)
{
	Cell *cell = myGrid.GetCellAtPosition(aPosition);
	if (cell == nullptr)
	{
		return -1;
	}
	return cell->tileId;
}
Bammi::Tile *Bammi::Board::GetTileAtIndex(int aIndex)
{
	if (aIndex == -1)
	{
		return nullptr;
	}
	return &myTiles[aIndex];
}
bool Bammi::Board::FillTile(TileIndex aIndex, int aPlayerIndex)
{
	auto &player = myPlayerManager->GetPlayer(aPlayerIndex);
	if (player.myTileCount >= myTiles.size())
	{
		return true;
	}
	auto &tile = myTiles[aIndex];
	tile.fillRate += 1;
	if (tile.playerIndex != aPlayerIndex)
	{
		player.myTileCount++;
		if (tile.playerIndex != -1)
		{
			auto &other = myPlayerManager->GetPlayer(tile.playerIndex);
			other.myTileCount--;
		}
	}
	tile.playerIndex = aPlayerIndex;
	if (tile.fillRate > tile.neighbors.size())
	{
		tile.fillRate = 1;
		for (auto &tile : tile.neighbors)
		{
			if (FillTile(tile, aPlayerIndex))
			{
				return true;
			} //turn into stack instead, so you can play it out with an animation
		}
	}
	return false;
}