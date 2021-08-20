#include "UIStateHandler.h"
void UIStateHandler::Init(SDL_Renderer* aRenderer)
{
	ButtonManager* buttonManager = new ButtonManager();
	int buttonIndex = buttonManager->CreateButton();
	Button& button = buttonManager->GetButton(buttonIndex);

	button.Init("assets/whitePixel.png", aRenderer);
	button.SetPosition({256,128});
	button.SetSize({300, 100});
	button.SetText("Hecc");
	button.SetOnClick([&](){PopState();});

    myLoadedStates["MainMenu"] = buttonManager; //This should be in a file or something in the future, probably next project

	UIStateHandler::GetInstance().PushState("MainMenu");
}
void UIStateHandler::PushState(ButtonManager* aState)
{
    myStates.push(aState);
}
void UIStateHandler::PushState(const std::string &aState)
{
    myStates.push(myLoadedStates[aState]);
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