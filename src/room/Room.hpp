#pragma once

#include <vector>
#include "Tile.hpp"
#include "GridPosition.hpp"
#include "PlacedFurniture.hpp"

class Room 
{
    public:
    Room(int width, int depth)
        : m_width{width}
        , m_depth{depth}
        , m_floorTiles(width * depth)
        , m_northWallTiles(m_northWallHeight * width)
        , m_eastWallTiles(m_eastWallHeight * depth)
    {}

    auto getWidth() const -> int { return m_width; }
    auto getDepth() const -> int { return m_depth; }
    auto getNorthWallHeight() const -> int { return m_northWallHeight; }
    auto getEastWallHeight() const -> int { return m_eastWallHeight; }

    auto getFloorTile(const GridPosition& position) -> Tile&
    {
        return m_floorTiles[position.row * m_width + position.column];
    }
    auto getFloorTile(const GridPosition& position) const -> const Tile&
    {
        return m_floorTiles[position.row * m_width + position.column];
    }
    auto getFloorTiles() -> std::vector<Tile>& { return m_floorTiles; }
    auto getFloorTiles() const -> const std::vector<Tile>& { return m_floorTiles; }
    
    auto getNorthWallTiles() -> std::vector<Tile>& { return m_northWallTiles; }
    auto getNorthWallTiles() const -> const std::vector<Tile>& { return m_northWallTiles; }
    auto getEastWallTiles() -> std::vector<Tile>& { return m_eastWallTiles; }
    auto getEastWallTiles() const -> const std::vector<Tile>& { return m_eastWallTiles; }
    
    auto getEastWallTile(const GridPosition& position) -> Tile&
    {
        return m_eastWallTiles[position.row * m_eastWallHeight + position.column];
    }
    auto getEastWallTile(const GridPosition& position) const -> const Tile&
    {
        return m_eastWallTiles[position.row * m_eastWallHeight + position.column];
    }
    auto getNorthWallTile(const GridPosition& position) -> Tile&
    {
        return m_northWallTiles[position.row * m_northWallHeight + position.column];
    }
    auto getNorthWallTile(const GridPosition& position) const -> const Tile&
    {
        return m_northWallTiles[position.row * m_northWallHeight + position.column];
    }
    private:
    int m_width {}, m_depth {}, m_northWallHeight{1}, m_eastWallHeight{1};
    std::vector<Tile> m_floorTiles {};
    std::vector<Tile> m_northWallTiles {};
    std::vector<Tile> m_eastWallTiles {};
    std::vector<PlacedFurniture> m_placedFurniture {};
};