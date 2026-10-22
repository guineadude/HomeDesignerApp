#pragma once

#include <optional>
#include "FurnitureInstanceID.hpp"

struct PlacementCell
{
    std::optional<FurnitureInstanceID> occupant {};
};