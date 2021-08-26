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

    for (size_t i = 0; i < myTextBoxes.size(); i++)
    {
        myTextBoxes[i].Update(aDeltaTime);
        if(!myTextBoxes[i].GetIsActive())
        {
            continue;
        }
        myTextBoxes[i].TryHover(mousePosF);
        if(input.GetMouseKeyPressed(1))
        {
            myTextBoxes[i].TryClick(mousePosF);
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

    for (size_t i = 0; i < myTextBoxes.size(); i++)
    {
        if(!myTextBoxes[i].GetIsActive())
        {
            continue;
        }
        myTextBoxes[i].Render();
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

int ButtonManager::CreateTextBox()
{
    myTextBoxes.emplace_back();
    return myTextBoxes.size() - 1;
}
TextBox& ButtonManager::GetTextBox(int aIndex)
{
    return myTextBoxes[aIndex];
}

bool ButtonManager::UpdateEvents(SDL_Event& aEvent)
{
    for(auto& textBox : myTextBoxes)
    {
        if(textBox.UpdateEvents(aEvent))
        {
            return true;
        }
    }
    return false;
}