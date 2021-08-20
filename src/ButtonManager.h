#pragma once
#include <vector>
#include "Button.h"

class ButtonManager
{
public:
    void Init();
    void Update(float aDeltaTime);
    void Render();
    int CreateButton();
    Button& GetButton(int aIndex);
private:
    std::vector<Button> myButtons;
};