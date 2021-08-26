#pragma once
#include <string>
#include "Text.h"
#include "Sprite.h"
#include "CollisionRect.h"

class TextBox
{
public:
    void Init(SDL_Renderer* aRenderer);
    void SetText(const std::string& aText);
    void SetTooltipText(const std::string& aText);
    const std::string& GetText();
    void Update(float aDeltaTime);
    bool UpdateEvents(SDL_Event& aEvent);
    void Render();
	void SetSize(Vector2f aSize);
	void SetPosition(Vector2f aPosition);
	void TryClick(Vector2f aClickPosition);
	void TryHover(Vector2f aMousePosition);
    inline void SetIsActive(bool aIsActive) {myIsActive = aIsActive;};
    inline bool GetIsActive() {return myIsActive;};
private:
    void HandleCaretBlink(float aDeltaTime);
    void HandleToolTip();
    void StartEditing();
    void StopEditing();
    CollisionRect myRect;
    std::string myTooltipText;
    std::string myInputText;
    Text myText;
    bool myIsEditing = false;
    bool myIsActive = true;
    SDL_Renderer* myRenderer;
    Sprite mySprite;
    Sprite myCaret;
    const float myCaretBlinkTime = 0.5f;
    float myCurrentBlinkTime = 0.f;
    bool myCaretVisible = true;
    Vector2f myPadding;
};