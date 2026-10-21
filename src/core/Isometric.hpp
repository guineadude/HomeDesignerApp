#pragma once

#include <SDL3/SDL.h>

#include "GridPosition.hpp"

namespace Isometric
{
    struct Projection
    {
        SDL_FPoint origin{};
        float stepX{};
        float stepY{};
    };

    [[nodiscard]] inline auto gridToScreen(const Projection& projection, const GridPosition& gridPos) -> SDL_FPoint
    {
        return {
            projection.origin.x + (static_cast<float>(gridPos.x) - static_cast<float>(gridPos.y)) * projection.stepX,
            projection.origin.y + (static_cast<float>(gridPos.x) + static_cast<float>(gridPos.y)) * projection.stepY
        };
    }
}