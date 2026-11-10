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

    [[nodiscard]] auto getCollider() const -> SDL_FRect { return m_bounds; }

    auto onClick() const -> void {}

private:
    SDL_FRect m_bounds {};
};
