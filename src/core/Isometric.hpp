#pragma once

#include <cmath>
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
        const float relativeX{screenPos.x - projection.origin.x};
        const float relativeY{screenPos.y - projection.origin.y};

        const float cx{relativeX / projection.stepX};
        const float cy{relativeY / projection.stepY};

        const float gridX{(cy + cx) * 0.5f};
        const float gridY{(cy - cx) * 0.5f};

        return {
        static_cast<int>(std::floor(gridX)),
        static_cast<int>(std::floor(gridY))
        };
    }
}