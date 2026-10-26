#pragma once

namespace PlacementGrid
{
    inline constexpr int cellsPerTile {9};
}

struct PlacementPosition
{
    int column {};
    int row {};
};