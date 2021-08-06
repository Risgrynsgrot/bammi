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
    int myTileCount = 0;
    Text myText;
};

struct Move
{
    int player;
    Bammi::TileIndex tile;
};

struct MoveResult
{
    bool validMove = false;
    int playerWon = -1;
};

class PlayerManager
{
public:
    void Init(SDL_Renderer* aRenderer, Bammi::Board* aBoard);
    int AddPlayer(const Player& aPlayer);
    MoveResult DoMove(Move aMove);
    void EndTurn();
    void EndGame();
    void Reset();
    Player& GetCurrentPlayer();
    int GetCurrentPlayerIndex();
    Player& GetPlayer(int aIndex);
    void Render();
    void Update();
    void SetPlayerListPosition(Vector2f aPosition);
    inline bool GameEnded() {return myGameEnded;};
private:
    void RenderWinner(int aPlayerIndex, Vector2f aPosition);
    void RenderPlayer(int aPlayerIndex, Vector2f aPosition);
    void RenderPlayerList();
    int myCurrentPlayer = 0;
    std::vector<Player> myPlayers;
    std::vector<Move> myMoves;
    Vector2f myPlayerListPosition;
    float myPlayerListOffset = 32;
    Bammi::Board* myBoard;
    bool myGameEnded;
    SDL_Renderer* myRenderer;
    Text myWinnerText;
};