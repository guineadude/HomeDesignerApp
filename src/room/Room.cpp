#include "Room.hpp"
#include "debug.hpp"

#include <algorithm>


auto Room::sortPlacedFurniture() -> void
{
    constexpr auto isLesserDepth = [](
        const PlacedFurniture& a,
        const PlacedFurniture& b)
    {
        const int aDepth{ a.position.column + a.position.row };
        const int bDepth{ b.position.column + b.position.row };

        return aDepth < bDepth;
    };

    std::ranges::sort(m_placedFurniture, isLesserDepth);
}

auto Room::canPlaceFurniture(PlacementPosition position, FurnitureFootprint footprint) const -> bool 
{
    // Core::Debug::log(
    //     "Position: ", position.column, ", ", position.row,
    //     " | Footprint: ", footprint.width, " x ", footprint.depth,
    //     " | Bounds: ", m_placementWidth, " x ", m_placementDepth
    // );

    if (footprint.width <= 0 || footprint.depth <= 0)
    {
        return false;
    }

    if (position.column < 0 || position.row < 0 ||
        position.column >= m_placementWidth ||
        position.row >= m_placementDepth)
    {
        return false;
    }

    if (footprint.width > m_placementWidth - position.column ||
        footprint.depth > m_placementDepth - position.row)
    {
        return false;
    }

    for (int r{0}; r < footprint.depth; ++r)
    {
        for (int c{0}; c < footprint.width; ++c)
        {
            const PlacementPosition cellPosition{
                position.column + c,
                position.row + r
            };

            Core::Debug::log(
                "Would occupy cell: column ", cellPosition.column,
                ", row ", cellPosition.row
            );
        }
    }

    return true;
} 