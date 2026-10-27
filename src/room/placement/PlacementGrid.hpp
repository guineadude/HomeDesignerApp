#pragma once

#include <utility>

namespace PlacementGrid
{
    inline constexpr int cellsPerTileAxis{2};
    inline constexpr int cellsPerTile{
        cellsPerTileAxis * cellsPerTileAxis
    };}

struct PlacementPosition
{
    int column{};
    int row{};

    PlacementPosition() = default;

    PlacementPosition(int x, int y)
        : column{x}
        , row{y}
    {
    }

    explicit PlacementPosition(const std::pair<int, int>& coordinates)
        : column{coordinates.first}
        , row{coordinates.second}
    {
    }
};