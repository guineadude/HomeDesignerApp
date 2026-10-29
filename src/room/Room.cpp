#include "Room.hpp"

auto Room::canPlaceFurniture(PlacementPosition position, FurnitureFootprint footprint) const -> bool
{
    //if footprint out of bounds
    if (footprint.width <= 0 || footprint.depth <= 0)
    {
        return false;
    }
    // if position out of bounds
    if (position.column < 0 || position.row < 0)
    {
        return false;
    }


    return true;
}