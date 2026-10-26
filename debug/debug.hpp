#pragma once

#include <SDL3/SDL.h>
#include <utility>
#include <sstream>

namespace debug
{
    template <typename... T>
    auto log(T&&... args) -> void
    {
        std::ostringstream message;
        (message << ... << std::forward<T>(args));

        SDL_Log("%s", message.str().c_str());
    }
}