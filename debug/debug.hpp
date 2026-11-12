#pragma once

#include <SDL3/SDL.h>
#include <sstream>

namespace Core
{
    namespace Debug
    {
        template <typename... T>
        auto log(T&&... args) -> void
        {
            std::ostringstream message;
            (message << ... << args);

            SDL_Log("%s", message.str().c_str());
        }
    }
}