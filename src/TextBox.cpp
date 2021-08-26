#include "TextBox.h"

void TextBox::Init(SDL_Renderer* aRenderer)
{
    const int textSize = 24;

    myPadding = {5, 5};

    myRenderer = aRenderer;
    mySprite.Init("assets/whitePixel.png", aRenderer);
    myRect.mySize = {200, textSize};
    myCaret.Init("assets/whitePixel.png", aRenderer);
    myCaret.SetSize(2, textSize);
    myText.Init("assets/hack.ttf", textSize, aRenderer);
    myText.SetColor(0,0,0);
}
void TextBox::SetText(const std::string& aText)
{
    myInputText = aText;
}
void TextBox::SetTooltipText(const std::string& aText)
{
    myTooltipText = aText;
}
const std::string& TextBox::GetText()
{
    return myInputText;
}
void TextBox::Update(float aDeltaTime)
{
    HandleToolTip();
    HandleCaretBlink(aDeltaTime);
}
bool TextBox::UpdateEvents(SDL_Event& aEvent)
{
    if(!myIsEditing)
    {
        return false;
    }

    switch(aEvent.type)
    {
        case SDL_TEXTINPUT:
            myInputText += aEvent.text.text;
        return true;
        case SDL_KEYDOWN:
            if(aEvent.key.keysym.sym == SDLK_BACKSPACE && !myInputText.empty())
            {
                myInputText.pop_back();
            }
            if(aEvent.key.keysym.sym == SDLK_ESCAPE)
            {
                StopEditing();
            }
        return true;
    }
    return false;
}
void TextBox::Render()
{
    mySprite.SetPosition(myRect.myPosition - myPadding);
    mySprite.SetSize(myRect.mySize + myPadding * 2.f);
    mySprite.Render();

    myText.SetPosition({myRect.myPosition.x, myRect.myPosition.x + myRect.mySize.y / 2.f});
    myText.Render(true, TextAlignment::Left, TextOrigin::Mid);

    if(myIsEditing)
    {
        if(myCaretVisible)
        {
            myCaret.SetPosition({myText.GetPosition().x + myText.GetSize().x, myText.GetPosition().y - myText.GetSize().y / 2.f});
            myCaret.Render();
        }
    }
}
void TextBox::TryClick(Vector2f aClickPosition)
{
    if (myRect.IsInside(aClickPosition))
    {
        StartEditing();
        return;
    }
    StopEditing();
}
void TextBox::TryHover(Vector2f aMousePosition)
{
    if (myRect.IsInside(aMousePosition))
    {
        mySprite.SetColorRGB(0.5, 0.5, 0.5);
        return;
    }
    mySprite.SetColorRGB(1,1,1);
}

void TextBox::StartEditing()
{
    SDL_StartTextInput();
    myIsEditing = true;
}
void TextBox::StopEditing()
{
    SDL_StopTextInput();
    myIsEditing = false;
}

void TextBox::SetSize(Vector2f aSize)
{
    myRect.mySize = aSize;
}
void TextBox::SetPosition(Vector2f aPosition)
{
    myRect.myPosition = aPosition;
}
void TextBox::HandleCaretBlink(float aDeltaTime) 
{
    myCurrentBlinkTime -= aDeltaTime;

    if(myCurrentBlinkTime < 0.f)
    {
        myCaretVisible = !myCaretVisible;
        myCurrentBlinkTime = myCaretBlinkTime;
    }
}
void TextBox::HandleToolTip()
{
    if(!myInputText.empty() || myIsEditing)
    {
        myText.SetText(myInputText.c_str());
        myText.SetColor(0,0,0);
        myCaret.SetColorRGB(0,0,0);
        return;
    }
    myText.SetText(myTooltipText.c_str());
    myText.SetColor(0.3, 0.3, 0.3);
    myCaret.SetColorRGB(0.3, 0.3, 0.3);
}