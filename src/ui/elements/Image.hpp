#pragma once

#include <SDL3/SDL.h>

class Image
{
public:
    [[nodiscard]] auto load([[maybe_unused]] SDL_Renderer* renderer) -> bool
    {
        return true;
    }

    auto render([[maybe_unused]] SDL_Renderer* renderer) const -> void
    {

    }

    [[nodiscard]] auto getCollider() const -> SDL_FRect { return m_bounds; }

    auto onHover(bool) -> void {}
    auto onPress(bool) -> void {}
    auto onRelease(bool) -> void {}

private:
    SDL_FRect m_bounds {};
};
