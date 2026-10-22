#pragma once

#include <SDL3/SDL.h>

namespace HitTest 
{
    inline auto handleMouseButtonDown(const SDL_MouseButtonEvent& buttonEvent) -> SDL_FPoint
    {
        auto x = buttonEvent.x;
        auto y = buttonEvent.y; 
        return SDL_FPoint{static_cast<float>(x), static_cast<float>(y)};
    }
}