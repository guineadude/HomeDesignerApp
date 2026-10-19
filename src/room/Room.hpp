#pragma once

#include <vector>
#include "Tile.hpp"
#include "GridPosition.hpp"

class Room 
{
    public:
    Room(int width, int depth)
        : m_width(width), m_depth(depth), m_tiles(width * depth)
    {}

    auto getWidth() const -> int { return m_width; }
    auto getDepth() const -> int { return m_depth; }
    auto getTile(const GridPosition& position) -> Tile&
    {
        return m_tiles[position.y * m_width + position.x];
    }
    auto getTile(const GridPosition& position) const -> const Tile&
    {
        return m_tiles[position.y * m_width + position.x];
    }
    auto getFloorTiles() -> std::vector<Tile>& { return m_tiles; }
    auto getFloorTiles() const -> const std::vector<Tile>& { return m_tiles; }

    private:
    int m_width {}, m_depth {};
    std::vector<Tile> m_tiles {};
};