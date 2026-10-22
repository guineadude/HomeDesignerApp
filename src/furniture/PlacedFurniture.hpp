#pragma once

#include "FurnitureDefinition.hpp"

using FurnitureInstanceID = std::size_t;

struct PlacedFurniture
{
    FurnitureInstanceID instanceId {};
    FurnitureID ID {};
    int column {};
    int row {};
};