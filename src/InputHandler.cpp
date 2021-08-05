#include "InputHandler.h"

bool InputHandler::UpdateEvents(SDL_Event& e)
{
    switch(e.type)
    {
    case SDL_KEYDOWN:
        HandleKeyDownEvent(e.key.keysym.sym);
        return true;
    case SDL_KEYUP:
        HandleKeyUpEvent(e.key.keysym.sym);
        return true;
    case SDL_MOUSEBUTTONDOWN:
        HandleMouseKeyDownEvent(e.button.button);
        return true;
    case SDL_MOUSEBUTTONUP:
        HandleMouseKeyUpEvent(e.button.button);
        return true;
    }
    return false;
}
void InputHandler::UpdateState()
{
    for (auto& pair : myKeyStatuses)
    {
        auto& key = pair.first;
        auto& status = pair.second;
		if (status == KeyStatus::Pressed)
		{
			myKeyStatuses[key] = KeyStatus::Down;
            continue;
		}
		if (status == KeyStatus::Released)
		{
			myKeyStatuses[key] = KeyStatus::Up;
		}
    }
    
}
void InputHandler::HandleKeyDownEvent(SDL_Keycode aKeyCode)
{
    if(myKeyStatuses[aKeyCode] == KeyStatus::Down)
    {
        return;
    }
    if(myKeyStatuses[aKeyCode] == KeyStatus::Pressed)
    {
        myKeyStatuses[aKeyCode] = KeyStatus::Down;
        return;
    }
    myKeyStatuses[aKeyCode] = KeyStatus::Pressed;
}
void InputHandler::HandleKeyUpEvent(SDL_Keycode aKeyCode)
{
    if(myKeyStatuses[aKeyCode] == KeyStatus::Up)
    {
        return;
    }
    if(myKeyStatuses[aKeyCode] == KeyStatus::Released)
    {
        myKeyStatuses[aKeyCode] = KeyStatus::Up;
        return;
    }
    myKeyStatuses[aKeyCode] = KeyStatus::Released;
}
void InputHandler::HandleMouseKeyDownEvent(int aMouseKey)
{
    if(myMouseKeyStatuses[aMouseKey] == KeyStatus::Down)
    {
        return;
    }
    if(myMouseKeyStatuses[aMouseKey] == KeyStatus::Pressed)
    {
        myMouseKeyStatuses[aMouseKey] = KeyStatus::Down;
        return;
    }
    myMouseKeyStatuses[aMouseKey] = KeyStatus::Pressed;
}
void InputHandler::HandleMouseKeyUpEvent(int aMouseKey)
{
    if(myMouseKeyStatuses[aMouseKey] == KeyStatus::Up)
    {
        return;
    }
    if(myMouseKeyStatuses[aMouseKey] == KeyStatus::Released)
    {
        myMouseKeyStatuses[aMouseKey] = KeyStatus::Up;
        return;
    }
    myMouseKeyStatuses[aMouseKey] = KeyStatus::Released;
}
bool InputHandler::GetKeyPressed(SDL_KeyCode aKeyCode)
{
    return myKeyStatuses[aKeyCode] == KeyStatus::Pressed;
}
bool InputHandler::GetKeyDown(SDL_KeyCode aKeyCode)
{
    return myKeyStatuses[aKeyCode] == KeyStatus::Down;
}
bool InputHandler::GetKeyReleased(SDL_KeyCode aKeyCode)
{
    return myKeyStatuses[aKeyCode] == KeyStatus::Released;
}
bool InputHandler::GetKeyUp(SDL_KeyCode aKeyCode)
{
    return myKeyStatuses[aKeyCode] == KeyStatus::Up;
}

bool InputHandler::GetMouseKeyPressed(int aMouseKey)
{
    return myMouseKeyStatuses[aMouseKey] == KeyStatus::Pressed;
}
bool InputHandler::GetMouseKeyDown(int aMouseKey)
{
    return myMouseKeyStatuses[aMouseKey] == KeyStatus::Down;
}
bool InputHandler::GetMouseKeyReleased(int aMouseKey)
{
    return myMouseKeyStatuses[aMouseKey] == KeyStatus::Released;
}
bool InputHandler::GetMouseKeyUp(int aMouseKey)
{
    return myMouseKeyStatuses[aMouseKey] == KeyStatus::Up;
}
Vector2i InputHandler::GetMousePosition()
{
	Vector2i mousePos;
	SDL_GetMouseState(&mousePos.x, &mousePos.y);
    return mousePos;
}