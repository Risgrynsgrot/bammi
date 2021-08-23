#include "UIStateHandler.h"
#include "WindowHandler.h"
#include <assert.h>

void UIStateHandler::Init(SDL_Renderer* aRenderer)
{
	ButtonManager* buttonManager = new ButtonManager();

    auto windowHandler = WindowHandler::GetInstance();

    const int spacing = 25;
    const int buttonCount = 2;

    Vector2i position = windowHandler->GetWindowSize() / 2;
    const Vector2f size(300.f, 100.f);
    position.y -= size.y * buttonCount;

    int buttonIndex = 0;
    for (size_t i = 0; i < buttonCount; i++)
    {
        buttonIndex = buttonManager->CreateButton();
        Button& button = buttonManager->GetButton(buttonIndex);

        button.Init("assets/whitePixel.png", aRenderer);
        button.SetPosition({position.x, position.y + i * (size.y + spacing)});
        button.SetSize(size);
    }
    
    int buttonStartIndex = buttonIndex - (buttonCount - 1);
    auto& startButton   = buttonManager->GetButton(buttonStartIndex);
    auto& optionsButton = buttonManager->GetButton(buttonStartIndex + 1);
    auto& creditsButton = buttonManager->GetButton(buttonStartIndex + 2);
    auto& quitButton    = buttonManager->GetButton(buttonStartIndex + 3);

	startButton.SetText("Start");
	startButton.SetOnClick([&](){PopState();});

    optionsButton.SetText("Options");
	optionsButton.SetOnClick([&](){PushState("Options");});

    creditsButton.SetText("Credits");
	creditsButton.SetOnClick([&](){PushState("Credits");});

	quitButton.SetText("Quit");
	quitButton.SetOnClick([&](){PopState();});

    myLoadedStates["mainmenu"] = buttonManager; //This should be in a file or something in the future, probably next project

	UIStateHandler::GetInstance().PushState("mainmenu");
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