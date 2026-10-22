#pragma once

namespace PlacementGrid
{
    inline constexpr int cellsPerTile {3};
}

struct PlacementPosition
{
    int column {};
    int row {};
};