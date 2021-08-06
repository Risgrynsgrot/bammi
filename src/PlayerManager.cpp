#include "PlayerManager.h"
#include "WindowHandler.h"

int PlayerManager::AddPlayer(const Player &aPlayer)
{
    myPlayers.push_back(aPlayer);
    myPlayers.back().myText.Init("assets/Hack.ttf", 24, myRenderer);

    return myPlayers.size() - 1;
}
MoveResult PlayerManager::DoMove(Move aMove)
{
    Bammi::Tile* tile = myBoard->GetTileAtIndex(aMove.tile);
    if (tile->playerIndex == -1 || tile->playerIndex == GetCurrentPlayerIndex())
    {
        bool won = myBoard->FillTile(aMove.tile, aMove.player);
        myMoves.push_back(aMove);
        if(won)
        {
            return {true, myCurrentPlayer};
        }
        return {true, -1};
    }
    return {false, -1};
}
void PlayerManager::EndTurn()
{
    myCurrentPlayer += 1;
    if (myCurrentPlayer >= myPlayers.size())
    {
        myCurrentPlayer = 0;
    }
}
void PlayerManager::EndGame()
{
    myGameEnded = true;
}
void PlayerManager::Reset()
{
    myGameEnded = false;
    myMoves.clear();
    for (size_t i = 0; i < myPlayers.size(); i++)
    {
        myPlayers[i].myTileCount = 0;
    }
    
}
Player &PlayerManager::GetCurrentPlayer()
{
    return myPlayers[myCurrentPlayer];
}
Player &PlayerManager::GetPlayer(int aIndex)
{
    return myPlayers[aIndex];
}
void PlayerManager::Render()
{
    RenderPlayerList();
    if(myGameEnded)
    {
        auto winnerPos = WindowHandler::GetInstance()->GetWindowSize();
        winnerPos.x /= 2;
        winnerPos.y = 32;
        RenderWinner(myCurrentPlayer, {(float)winnerPos.x, (float)winnerPos.y});
    }
}
void PlayerManager::RenderWinner(int aPlayerIndex, Vector2f aPosition)
{
    Player &player = myPlayers[aPlayerIndex];

    myWinnerText.SetColor(player.myColor.r, player.myColor.g, player.myColor.b);
    myWinnerText.SetPosition(aPosition);
    char buffer[128];
    int written = sprintf(buffer, "%s won in %zu moves!", player.myName.c_str(), myMoves.size()); //Add how many tiles you own
    myWinnerText.SetText(buffer);
    myWinnerText.Render(false, TextAlignment::Center);
}
void PlayerManager::RenderPlayerList()
{
    for (size_t i = 0; i < myPlayers.size(); i++)
    {
        Vector2f position = {myPlayerListPosition.x, myPlayerListPosition.y + myPlayerListOffset * i};
        RenderPlayer(i, position);
    }
}
void PlayerManager::RenderPlayer(int aPlayerIndex, Vector2f aPosition)
{
    Player &player = myPlayers[aPlayerIndex];

    player.myText.SetColor(player.myColor.r, player.myColor.g, player.myColor.b);
    player.myText.SetPosition(aPosition);
    char buffer[128];
    int written = sprintf(buffer, "%s: %d", player.myName.c_str(), player.myTileCount); //Add how many tiles you own
    if (aPlayerIndex == myCurrentPlayer)
    {
        sprintf(buffer + written, " *");
    }
    player.myText.SetText(buffer);
    player.myText.Render(false);
}
void PlayerManager::Init(SDL_Renderer *aRenderer, Bammi::Board* aBoard)
{
    myRenderer = aRenderer;
    myBoard = aBoard;
    myWinnerText.Init("assets/Hack.ttf", 48, myRenderer);
}
void PlayerManager::SetPlayerListPosition(Vector2f aPosition)
{
    myPlayerListPosition = aPosition;
}
void PlayerManager::Update()
{
    auto windowSize = WindowHandler::GetInstance()->GetWindowSize();
    windowSize.y /= 2;
    windowSize.x = 32;
    myPlayerListPosition = {(float)windowSize.x, (float)windowSize.y};
}
int PlayerManager::GetCurrentPlayerIndex()
{
    return myCurrentPlayer;
}