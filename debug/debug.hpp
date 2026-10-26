#pragma once

#include <SDL3/SDL.h>
#include <utility>

namespace debug
{
    inline auto log(const char* message) -> void
    {
        SDL_Log("%s", message);
    }

    template <typename... Args>
    inline auto log(const char* format, Args&&... args) -> void
    {
        SDL_Log(format, std::forward<Args>(args)...);
    }
}