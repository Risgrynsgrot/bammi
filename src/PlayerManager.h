#pragma once
#include "Primitives.h"
#include <vector>
#include <string>
#include "BammiBoard.h"
#include "Text.h"

struct Player
{
    Color myColor;
    std::string myName;
};

struct Move
{
    int player;
    Bammi::TileIndex tile;
};

class PlayerManager
{
public:
    void Init(SDL_Renderer* aRenderer, Bammi::Board* aBoard);
    int AddPlayer(const Player& aPlayer);
    bool DoMove(Move aMove);
    void EndTurn();
    Player& GetCurrentPlayer();
    int GetCurrentPlayerIndex();
    Player& GetPlayer(int aIndex);
    void Render();
    void Update();
    void SetPlayerListPosition(Vector2f aPosition);
private:
    void RenderPlayer(int aPlayerIndex, Vector2f aPosition);
    void RenderPlayerList();
    int myTurn = 0;
    int myCurrentPlayer = 0;
    std::vector<Player> myPlayers;
    std::vector<Move> myMoves;
    Text myText;
    Vector2f myPlayerListPosition;
    float myPlayerListOffset = 32;
    Bammi::Board* myBoard;
};