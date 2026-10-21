#pragma once

#include <SDL3/SDL.h>

#include "GridPosition.hpp"

namespace Isometric
{
    namespace Constants
    {
        inline constexpr float TileStepX{64.0f};
        inline constexpr float TileStepY{32.0f};
    }

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

    [[nodiscard]] inline auto screenToGrid(const Projection& projection, const SDL_FPoint& screenPos) -> GridPosition
    {
        return GridPosition{0,0};
    }
}