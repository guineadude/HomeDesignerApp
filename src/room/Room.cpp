#include "Room.hpp"
#include "debug.hpp"

#include <algorithm>

auto Room::tryPlaceFurniture(
    const FurnitureDefinition& furniture,
    PlacementPosition position) -> std::optional<FurnitureInstanceID>
{
    if (!canPlaceFurniture(position, furniture.footprint))
    {
        return std::nullopt;
    }

    const FurnitureInstanceID instanceID{ getIncrementedFurnitureID() };

    m_placedFurniture.push_back(PlacedFurniture{
        instanceID,
        furniture.id,
        position,
        furniture.footprint
    });


    occupyCells(position, furniture.footprint, instanceID);

    sortPlacedFurniture();

//-----------------------------DEBUG-------------------------
    Core::Debug::log(
        furniture.name, " placed at: (", position.column, ", ", position.row, ")"
    );
    for (int row{0}; row < furniture.footprint.depth; ++row)
    {
        for (int column{0}; column < furniture.footprint.width; ++column)
        {
            Core::Debug::log(
                "  Occupies tile: (",
                position.column + column, ", ", position.row + row, ")"
            );
        }
    }
//-----------------------------DEBUG END-------------------------

    return instanceID;
}

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
    // check room bounds
    if (position.column < 0 || position.row < 0 ||
        position.column >= m_placementWidth ||
        position.row >= m_placementDepth)
    {
        return false;
    }

    // check footprint fits in room
    if (footprint.width > m_placementWidth - position.column ||
        footprint.depth > m_placementDepth - position.row)
    {
        return false;
    }

    //check each cell based on footprint for occupancy
    for (int r{0}; r < footprint.depth; ++r)
    {
        for (int c{0}; c < footprint.width; ++c)
        {
            const PlacementPosition cellPosition{
                position.column + c,
                position.row + r
            };
            
            if (m_placementCells[placementCellIndex(cellPosition)].occupant)
            {
                return false;
            }
        }
    }

    return true;
} 

auto Room::occupyCells(PlacementPosition position, FurnitureFootprint footprint, FurnitureInstanceID instanceID) -> void
{
    for (int r{0}; r < footprint.depth; ++r)
    {
        for (int c{0}; c < footprint.width; ++c)
        {
            const PlacementPosition cellPosition{
                position.column + c,
                position.row + r
            };

            m_placementCells[placementCellIndex(cellPosition)].occupant = instanceID;
        }
    }
}