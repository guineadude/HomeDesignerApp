#pragma once

#include <cmath>
#include <SDL3/SDL.h>
#include <utility>

#include "placement/GridPosition.hpp"

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
    
    [[nodiscard]]
    inline auto gridToWorld(const Projection& projection, const GridPosition& gridPos) -> SDL_FPoint
    {
        return {
            projection.origin.x + (static_cast<float>(gridPos.column) - static_cast<float>(gridPos.row)) * projection.stepX,
            projection.origin.y + (static_cast<float>(gridPos.column) + static_cast<float>(gridPos.row)) * projection.stepY
        };
    }

    [[nodiscard]] 
    inline auto worldToGrid(const Projection& projection, const SDL_FPoint& worldPos) -> std::pair<int,int>
    {
        //relative world position with respect to the origin of the projection
        const float relativeX{worldPos.x - projection.origin.x};
        const float relativeY{worldPos.y - projection.origin.y};

        //convert relative world position to grid coordinates in isometric space
        const float cx{relativeX / projection.stepX};
        const float cy{relativeY / projection.stepY};

        //apply vector math for grid coords
        const float gridColumn{(cy + cx) * 0.5f};
        const float gridRow{(cy - cx) * 0.5f};

        //round down to get grid integer coordinates and return
        return {
        static_cast<int>(std::floor(gridColumn)),
        static_cast<int>(std::floor(gridRow))
        };
    }
    
}