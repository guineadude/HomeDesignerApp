#pragma once

#include <SDL3/SDL.h>

namespace HitTest 
{
    inline auto handleMouseButtonDown(const SDL_MouseButtonEvent& buttonEvent) -> void
    {
        auto x = buttonEvent.x;
        auto y = buttonEvent.y; 
        SDL_Log("Mouse button down at (%f, %f)", x, y);
    }
}