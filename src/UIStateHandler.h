#pragma once
#include <stack>
#include "ButtonManager.h"
#include "robin_hood.h"

class Game;

class UIStateHandler
{
public:
    void            Init(SDL_Renderer* aRenderer, Game& aGame);
    void            PushState(ButtonManager* aState);
    void            PushState(const std::string& aState); //To allow for adding from file in the future
    void            PopState();
    ButtonManager&  GetTop();
    void            Update(float aDeltaTime);
    bool            UpdateEvents(SDL_Event& aEvent);
    void            Render();

    static inline UIStateHandler &GetInstance()
    {
        static UIStateHandler myInstance;
        return myInstance;
    };
private:
    std::stack<ButtonManager*> myStates;
    robin_hood::unordered_map<std::string, ButtonManager*> myLoadedStates;
};