#pragma once

#include <SDL3/SDL.h>

namespace Collision
{
    inline auto checkMouseHit(const SDL_FPoint& mouse, const SDL_FRect& rect) -> bool
    {
        return mouse.x >= rect.x && mouse.x <= rect.x + rect.w &&
               mouse.y >= rect.y && mouse.y <= rect.y + rect.h;
    }
}