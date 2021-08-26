#pragma once
#include <vector>
#include "Button.h"
#include "TextBox.h"

class ButtonManager
{
public:
    void Init();
    void Update(float aDeltaTime);
    bool UpdateEvents(SDL_Event& aEvent);
    void Render();
    int CreateButton();
    Button& GetButton(int aIndex);

    int CreateTextBox();
    TextBox& GetTextBox(int aIndex);
private:
    std::vector<Button> myButtons;
    std::vector<TextBox> myTextBoxes;
};