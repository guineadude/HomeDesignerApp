#pragma once

#include <SDL3/SDL.h>
#include <string>

#include "FurnitureFootprint.hpp"

enum class FurnitureID
{
    WoodenBed,
    WoodenCupboard,
    BedsideTable,
    WoodenTable,
    PottedPlant
};

struct FurnitureDefinition
{
    std::string name {};
    std::string texturePath {};
    FurnitureFootprint footprint {};
    int price {1};
    SDL_FPoint drawOffset {};
};