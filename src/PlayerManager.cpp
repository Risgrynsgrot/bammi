#include "PlayerManager.h"
#include "WindowHandler.h"

int PlayerManager::AddPlayer(const Player &aPlayer)
{
    myPlayers.push_back(aPlayer);

    return myPlayers.size() - 1;
}
bool PlayerManager::DoMove(Move aMove)
{
    Bammi::Tile* tile = myBoard->GetTileAtIndex(aMove.tile);
    if (tile->playerIndex == -1 || tile->playerIndex == GetCurrentPlayerIndex())
    {
        myBoard->FillTile(aMove.tile, aMove.player);
        myMoves.push_back(aMove);
        return true;
    }
    return false;
}
void PlayerManager::EndTurn()
{
    myCurrentPlayer += 1;
    if (myCurrentPlayer >= myPlayers.size())
    {
        myCurrentPlayer = 0;
    }
    myTurn++;
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
    RenderTurn();
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

    myText.SetColor(player.myColor.r, player.myColor.g, player.myColor.b);
    myText.SetPosition(aPosition);
    char buffer[128];
    int written = sprintf(buffer, "%s: ", player.myName.c_str()); //Add how many tiles you own
    if (aPlayerIndex == myCurrentPlayer)
    {
        sprintf(buffer + written, " *");
    }
    myText.SetText(buffer);
    myText.Render();
}
void PlayerManager::RenderTurn()
{
}
void PlayerManager::Init(SDL_Renderer *aRenderer, Bammi::Board* aBoard)
{
    myText.Init("assets/hack.ttf", 24, aRenderer);
    myBoard = aBoard;
}
void PlayerManager::SetPlayerListPosition(Vector2f aPosition)
{
    myPlayerListPosition = aPosition;
}
void PlayerManager::Update()
{
    auto windowSize = WindowHandler::GetInstance()->GetWindowSize();
    windowSize.y /= 2;
    windowSize.x /= 4;
    myPlayerListPosition = {windowSize.x, windowSize.y};
}
int PlayerManager::GetCurrentPlayerIndex()
{
    return myCurrentPlayer;
}