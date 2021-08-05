#pragma once
#include <SDL.h>
#include "Grid.h"
#include "Sprite.h"
#include "BammiBoard.h"
#include "Text.h"
#include "PlayerManager.h"

class Game
{
public:
	void Init(SDL_Renderer* aRenderer);
	void Start();
	void Update(float aDeltaTime);
	void Render();
	void Quit();
private:
	void FillTile(int aTileIndex, int aPlayerIndex);
	PlayerManager myPlayerManager;
	Sprite mySprite;
	Sprite myRectangle;
	SDL_Renderer* myRenderer;
	Bammi::Board myBoard;
	Text myText;
};