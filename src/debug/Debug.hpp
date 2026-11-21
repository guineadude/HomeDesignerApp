#pragma once

#include <SDL3/SDL.h>
#include <sstream>

class FurnitureCatalogue;
struct FurnitureDefinition;

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

namespace Catalogue
{
    namespace Debug
    {
        auto cycleFurnitureCatalogue(const FurnitureCatalogue& catalogue) -> void;
        [[nodiscard]] auto getCurrentFurnitureDefinition(const FurnitureCatalogue& catalogue) -> const FurnitureDefinition&;
    }
}
