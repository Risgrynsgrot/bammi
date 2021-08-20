#include "ButtonManager.h"
#include "InputHandler.h"

void ButtonManager::Init()
{

}
void ButtonManager::Update(float aDeltaTime)
{
	InputHandler& input = InputHandler::GetInstance();
	auto mousePos = input.GetMousePosition();
	Vector2f mousePosF = {(float)mousePos.x, (float)mousePos.y};

    for (size_t i = 0; i < myButtons.size(); i++)
    {
        if(!myButtons[i].GetIsActive())
        {
            continue;
        }
        myButtons[i].TryHover(mousePosF);
        if(input.GetMouseKeyPressed(1))
        {
            myButtons[i].TryClick(mousePosF);
        }
    }
    
}

void ButtonManager::Render()
{
    for (size_t i = 0; i < myButtons.size(); i++)
    {
        if(!myButtons[i].GetIsActive())
        {
            continue;
        }
        myButtons[i].Render();
    }
}

int ButtonManager::CreateButton()
{
    myButtons.emplace_back();
    return myButtons.size() - 1;
}
Button& ButtonManager::GetButton(int aIndex)
{
    return myButtons[aIndex];
}