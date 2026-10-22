#pragma once

#include "FurnitureDefinition.hpp"
#include "placement/PlacementGrid.hpp"
#include "FurnitureInstanceId.hpp"

struct PlacedFurniture
{
    FurnitureInstanceID instanceId {};
    FurnitureID ID {};

    PlacementPosition position {};
    FurnitureFootprint footprint {};
};