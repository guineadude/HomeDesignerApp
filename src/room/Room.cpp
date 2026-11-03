#include "Room.hpp"
#include "debug.hpp"

#include <algorithm>

auto Room::tryPlaceFurniture(const FurnitureDefinition& furniture, PlacementPosition position) -> std::optional<FurnitureInstanceID>
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

//-----------------------------DEBUG-------------------------//
    forEachFootprintCell(position, furniture.footprint, [&](PlacementPosition p){
        Core::Debug::log("  Cell: (", p.column, ", ", p.row, ")");
    });
//-----------------------------DEBUG_END---------------------//

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
    // Check room bounds.
    if (position.column < 0 || position.row < 0 ||
        position.column >= m_placementWidth ||
        position.row >= m_placementDepth)
    {
        return false;
    }

    // Check that the entire footprint fits in the room.
    if (footprint.width > m_placementWidth - position.column ||
        footprint.depth > m_placementDepth - position.row)
    {
        return false;
    }
    
    return allFootprintCells(position, footprint, [&](PlacementPosition p) {
        return !m_placementCells[placementCellIndex(p)].occupant;
    });
} 

auto Room::occupyCells(PlacementPosition position, FurnitureFootprint footprint, FurnitureInstanceID instanceID) -> void
{
    forEachFootprintCell(position, footprint, [&](PlacementPosition p){
        m_placementCells[placementCellIndex(p)].occupant = instanceID;
    });
}