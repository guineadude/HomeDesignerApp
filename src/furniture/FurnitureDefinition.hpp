#pragma once

#include <SDL3/SDL.h>

#include <string>

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
    int rows {1}, columns {1};
    int price {1};
    SDL_FPoint drawOffset {};
};