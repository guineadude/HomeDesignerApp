#pragma once

#include <vector>

#include "room/Tile.hpp"
#include "furniture/FurnitureDefinition.hpp"
#include "room/placement/PlacementGrid.hpp"

struct FurniturePlacement
{
    FurnitureUniqueID id{};
    PlacementPosition position{};
};

struct RoomBuildInstructions
{
    int width{3};
    int depth{5};
    FloorType floorType     { FloorType::Debug };
    WallType  northWallType { WallType::Debug  };
    WallType  eastWallType  { WallType::Debug  };
    std::vector<FurniturePlacement> furniture {};
};
