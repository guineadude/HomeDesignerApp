    #include "Room.hpp"
    #include "debug.hpp"

auto Room::canPlaceFurniture(
    PlacementPosition position,
    FurnitureFootprint footprint) const -> bool
{
    if (footprint.width <= 0 || footprint.depth <= 0)
    {
        return false;
    }

    if (position.column < 0 || position.row < 0)
    {
        return false;
    }

    if (position.column + footprint.width > m_placementWidth ||
        position.row + footprint.depth > m_placementDepth)
    {
        return false;
    }

    for (int r{0}; r < footprint.depth; ++r)
    {
        for (int c{0}; c < footprint.width; ++c)
        {
            const int row{position.row + r};
            const int column{position.column + c};

        Core::Debug::log(
            "Position: ", position.column, ", ", position.row,
            " | Footprint: ", footprint.width, " x ", footprint.depth,
            " | Bounds: ", m_placementWidth, " x ", m_placementDepth
        );
        }
    }

    return true;
}