#pragma once

enum class FloorType
{
    Wood,
    Stone
};

struct Tile
{
    FloorType floorType{FloorType::Wood};
};