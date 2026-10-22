#pragma once

#include <cmath>
#include <SDL3/SDL.h>

#include "../room/placement/GridPosition.hpp"

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
            projection.origin.x +             (static_cast<float>(gridPos.column) - static_cast<float>(gridPos.row)) * projection.stepX,
                        projection.origin.y + (static_cast<float>(gridPos.column) + static_cast<float>(gridPos.row)) * projection.stepY
        };
    }

    [[nodiscard]] inline auto screenToGrid(const Projection& projection, const SDL_FPoint& screenPos) -> GridPosition
    {
        //relative screen position with respect to the origin of the projection
        const float relativeX{screenPos.x - projection.origin.x};
        const float relativeY{screenPos.y - projection.origin.y};

        //convert relative screen position to grid coordinates in isometric space
        const float cx{relativeX / projection.stepX};
        const float cy{relativeY / projection.stepY};

        //
        const float gridColumn{(cy + cx) * 0.5f};
        const float gridRow{(cy - cx) * 0.5f};

        return {
        static_cast<int>(std::floor(gridColumn)),
        static_cast<int>(std::floor(gridRow))
        };
    }
}