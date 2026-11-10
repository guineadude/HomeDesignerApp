#pragma once

#include <SDL3/SDL.h>

class Label
{
public:
    [[nodiscard]] auto load(SDL_Renderer* renderer) -> bool
    {
        return true;
    }

    auto render(SDL_Renderer* renderer) const -> void
    {

    }
};
