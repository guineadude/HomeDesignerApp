#pragma once

#include <SDL3/SDL.h>
#include <string>

#include "FurnitureFootprint.hpp"

enum class FurnitureUniqueID
{
    WoodenBed,
    WoodenCupboard,
    BedsideTable,
    WoodenTable,
    PottedPlant
};

struct FurnitureDefinition
{
    FurnitureUniqueID id{};
    std::string name{};
    std::string texturePath{};
    FurnitureFootprint footprint{};
    int price{};
    SDL_FPoint drawOffset{};
    float spriteScale{1.0f};
};