#include "UIStateHandler.h"
#include "WindowHandler.h"
#include <assert.h>
#include <iostream>
#include "Game.h"

void UIStateHandler::Init(SDL_Renderer* aRenderer, Game& aGame)
{
	ButtonManager* mainMenu = new ButtonManager();
	ButtonManager* gameMenu = new ButtonManager();

    auto windowHandler = WindowHandler::GetInstance();

    const int spacing = 25;
    const int buttonCount = 4;

    Vector2i position = windowHandler->GetWindowSize() / 2;
    const Vector2f size(300.f, 100.f);
    position.y -= size.y * buttonCount;

    int buttonIndex = 0;
    for (size_t i = 0; i < buttonCount; i++)
    {
        buttonIndex = mainMenu->CreateButton();
    }

    int textBoxIndex = mainMenu->CreateTextBox();

    auto& textBox = mainMenu->GetTextBox(textBoxIndex);
    textBox.Init(aRenderer);
    textBox.SetTooltipText("IP address...");
    textBox.SetPosition({128, 128});
    
    int buttonStartIndex = buttonIndex - (buttonCount - 1);
    auto& startButton   = mainMenu->GetButton(buttonStartIndex);
    auto& optionsButton = mainMenu->GetButton(buttonStartIndex + 1);
    auto& creditsButton = mainMenu->GetButton(buttonStartIndex + 2);
    auto& quitButton    = mainMenu->GetButton(buttonStartIndex + 3);

    startButton.Init("assets/whitePixel.png", aRenderer);
	startButton.SetText("Start");
	startButton.SetOnClick([&]()
    {
        PopState();
        PushState("game");
        aGame.Start();
    });
    startButton.SetPosition({position.x, position.y + 0 * (size.y + spacing)});
    startButton.SetSize(size);

    optionsButton.Init("assets/whitePixel.png", aRenderer);
    optionsButton.SetText("Options");
	optionsButton.SetOnClick([&](){PushState("Options");});
    optionsButton.SetPosition({position.x, position.y + 1 * (size.y + spacing)});
    optionsButton.SetSize(size);

    creditsButton.Init("assets/whitePixel.png", aRenderer);
    creditsButton.SetText("Credits");
	creditsButton.SetOnClick([&](){PushState("Credits");});
    creditsButton.SetPosition({position.x, position.y + 2 * (size.y + spacing)});
    creditsButton.SetSize(size);

    quitButton.Init("assets/whitePixel.png", aRenderer);
	quitButton.SetText("Quit");
	quitButton.SetOnClick([&](){quitButton.SetText("nah");});
    quitButton.SetPosition({position.x, position.y + 3 * (size.y + spacing)});
    quitButton.SetSize(size);

    myLoadedStates["mainmenu"] = mainMenu; //This should be in a file or something in the future, probably next project
    myLoadedStates["game"] = gameMenu;

	PushState("mainmenu");
}
void UIStateHandler::PushState(ButtonManager* aState)
{
    myStates.push(aState);
}
void UIStateHandler::PushState(const std::string &aState)
{
    assert(myLoadedStates.find(aState) != myLoadedStates.end());

    auto state = myLoadedStates[aState];
    myStates.push(state);
}
void UIStateHandler::PopState()
{
    myStates.pop();
}
ButtonManager &UIStateHandler::GetTop()
{
    return *myStates.top();
}
void UIStateHandler::Update(float aDeltaTime)
{
    if(myStates.empty())
        return;

    myStates.top()->Update(aDeltaTime);
}
void UIStateHandler::Render()
{
    if(myStates.empty())
        return;

    myStates.top()->Render();
}

bool UIStateHandler::UpdateEvents(SDL_Event& aEvent)
{
    if(myStates.empty())
        return false;

    return myStates.top()->UpdateEvents(aEvent);
}