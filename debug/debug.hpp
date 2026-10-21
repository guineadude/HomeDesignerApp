#pragma once

#include <SDL3/SDL.h>

namespace debug
{
    inline auto log(const char* message) -> void
    {
        SDL_Log("%s", message);
    }
}