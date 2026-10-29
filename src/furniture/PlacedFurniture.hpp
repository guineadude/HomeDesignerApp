#pragma once

#include "FurnitureDefinition.hpp"
#include "placement/PlacementGrid.hpp"
#include "FurnitureInstanceID.hpp"

struct PlacedFurniture
{
    FurnitureInstanceID instanceID {};
    FurnitureUniqueID   uniqueID   {};
    PlacementPosition   position   {};
    FurnitureFootprint  footprint  {};
};