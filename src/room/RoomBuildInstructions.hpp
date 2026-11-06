#pragma once

#include <vector>

#include "Tile.hpp"
#include "furniture/FurnitureDefinition.hpp"
#include "placement/PlacementGrid.hpp"

struct FurniturePlacement
{
    FurnitureUniqueID id{};
    PlacementPosition position{};
};

// Plain data describing how to build a room; intended to be what a save file stores.
struct RoomBuildInstructions
{
    int width{3};
    int depth{3};
    FloorType floorType     { FloorType::Debug };
    WallType  northWallType { WallType::Debug  };
    WallType  eastWallType  { WallType::Debug  };
    std::vector<FurniturePlacement> furniture {};
};
