#pragma once
#include "Vector2.h"
#include <SDL.h>
#include "robin_hood.h"

enum struct KeyStatus
{
    Up,
    Pressed,
    Down,
    Released
};

class InputHandler
{
public:

    bool UpdateEvents(SDL_Event& e);
    void UpdateState();

    Vector2i GetMousePosition();

    bool GetKeyPressed(SDL_KeyCode aKeyCode);
    bool GetKeyDown(SDL_KeyCode aKeyCode);
    bool GetKeyReleased(SDL_KeyCode aKeyCode);
    bool GetKeyUp(SDL_KeyCode aKeyCode);

    bool GetMouseKeyPressed (int aMouseKey);
    bool GetMouseKeyDown    (int aMouseKey);
    bool GetMouseKeyReleased(int aMouseKey);
    bool GetMouseKeyUp      (int aMouseKey);

    static inline InputHandler &GetInstance()
    {
        static InputHandler myInstance;
        return myInstance;
    };

private:
    void HandleKeyDownEvent(SDL_Keycode aKeyCode);
    void HandleKeyUpEvent(SDL_Keycode aKeyCode);
    void HandleMouseKeyDownEvent(int aMouseKey);
    void HandleMouseKeyUpEvent(int aMouseKey);
    robin_hood::unordered_map<SDL_Keycode, KeyStatus> myKeyStatuses;
    robin_hood::unordered_map<int, KeyStatus> myMouseKeyStatuses;
};