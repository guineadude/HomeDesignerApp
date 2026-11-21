#pragma once

#include <optional>
#include "furniture/FurnitureInstanceID.hpp"

struct PlacementCell
{
    std::optional<FurnitureInstanceID> occupant {};
};