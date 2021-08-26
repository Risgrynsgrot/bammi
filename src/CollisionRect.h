#pragma once
#include "Vector2.h"

struct CollisionRect
{
    bool IsInside(Vector2f aPosition);
    Vector2f myPosition;
    Vector2f mySize;
};