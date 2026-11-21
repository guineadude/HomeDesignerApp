#pragma once

#include "furniture/FurnitureDefinition.hpp"
#include "room/placement/PlacementGrid.hpp"
#include "furniture/FurnitureInstanceID.hpp"

struct PlacedFurniture
{
    FurnitureInstanceID instanceID {};
    FurnitureUniqueID   uniqueID   {};
    PlacementPosition   position   {};
    FurnitureFootprint  footprint  {};
};