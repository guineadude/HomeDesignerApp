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
    FloorType floorType     { FloorType::Wood      };
    WallType  northWallType { WallType::Bone       };
    WallType  eastWallType  { WallType::WoodBright };
    std::vector<FurniturePlacement> furniture {};
};
