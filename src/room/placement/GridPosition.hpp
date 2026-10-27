#pragma once
#include <utility>

struct GridPosition
{
    int column{};
    int row{};

    GridPosition() = default;

    GridPosition(int columnValue, int rowValue)
        : column{columnValue}
        , row{rowValue}
    {
    }

    explicit GridPosition(const std::pair<int, int>& c)
        : column{c.first}
        , row{c.second}
    {
    }
};