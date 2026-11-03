#pragma once

#include <optional>
#include <vector>
#include "Tile.hpp"
#include "placement/GridPosition.hpp"
#include "placement/PlacementCell.hpp"
#include "placement/PlacementGrid.hpp"
#include "furniture/FurnitureFootprint.hpp"
#include "furniture/FurnitureInstanceID.hpp"
#include "furniture/PlacedFurniture.hpp"

class Room 
{
public:
    Room(int width, int depth)
    : m_width{width}
    , m_depth{depth}
    , m_placementWidth{width * PlacementGrid::cellsPerTileAxis}
    , m_placementDepth{depth * PlacementGrid::cellsPerTileAxis}
    , m_floorTiles{ static_cast<std::size_t>(width * depth) }
    , m_northWallTiles{ static_cast<std::size_t>(m_northWallHeight * width) }
    , m_eastWallTiles{ static_cast<std::size_t>(m_eastWallHeight * depth) }
    , m_placementCells{ static_cast<std::size_t>(m_placementWidth * m_placementDepth) }
    {}

    //getters
    [[nodiscard]] auto getWidth() const -> int { return m_width; }
    [[nodiscard]] auto getDepth() const -> int { return m_depth; }
    [[nodiscard]] auto getNorthWallHeight() const -> int { return m_northWallHeight; }
    [[nodiscard]] auto getEastWallHeight() const -> int { return m_eastWallHeight; }
    [[nodiscard]] auto getPlacementWidth() const -> int { return m_placementWidth; }
    [[nodiscard]] auto getPlacementDepth() const -> int { return m_placementDepth; }
    
    //floor tiles getters
    [[nodiscard]] auto getFloorTile(const GridPosition& position) -> Tile& 
    { 
        return m_floorTiles[position.row * m_width + position.column]; 
    }
    [[nodiscard]] auto getFloorTile(const GridPosition& position) const -> const Tile& 
    {
        return m_floorTiles[position.row * m_width + position.column]; 
    }
    [[nodiscard]] auto getFloorTiles() -> std::vector<Tile>& { return m_floorTiles; }
    [[nodiscard]] auto getFloorTiles() const -> const std::vector<Tile>& { return m_floorTiles; }
    
    //wall tiles getters
    [[nodiscard]] auto getEastWallTile(const GridPosition& position) -> Tile& 
    {
        return m_eastWallTiles[position.row * m_eastWallHeight + position.column];
    }
    [[nodiscard]] auto getEastWallTile(const GridPosition& position) const -> const Tile& 
    {
        return m_eastWallTiles[position.row * m_eastWallHeight + position.column];
    }
    [[nodiscard]] auto getNorthWallTile(const GridPosition& position) -> Tile& 
    {
        return m_northWallTiles[position.row * m_northWallHeight + position.column];
    }
    [[nodiscard]] auto getNorthWallTile(const GridPosition& position) const -> const Tile& 
    {
        return m_northWallTiles[position.row * m_northWallHeight + position.column];
    }
    [[nodiscard]] auto getNorthWallTiles() -> std::vector<Tile>& { return m_northWallTiles; }
    [[nodiscard]] auto getNorthWallTiles() const -> const std::vector<Tile>& { return m_northWallTiles; }
    [[nodiscard]] auto getEastWallTiles() -> std::vector<Tile>& { return m_eastWallTiles; }
    [[nodiscard]] auto getEastWallTiles() const -> const std::vector<Tile>& { return m_eastWallTiles; }
    
    [[nodiscard]] auto getPlacedFurniture() const -> const std::vector<PlacedFurniture>& { return m_placedFurniture; }

    //furniture
    [[nodiscard]] auto tryPlaceFurniture(
        const FurnitureDefinition& furniture,
        PlacementPosition position) -> std::optional<FurnitureInstanceID>;
        [[nodiscard]] auto canPlaceFurniture(PlacementPosition position, FurnitureFootprint footprint) const -> bool;
        auto sortPlacedFurniture() -> void;
        auto occupyCells(PlacementPosition position, FurnitureFootprint footprint, FurnitureInstanceID instanceID) -> void;
        private:
        // room dimensions and wall heights
        int m_width {}, m_depth {}, m_northWallHeight{1}, m_eastWallHeight{1};
    // placement grid size
    int m_placementWidth{}, m_placementDepth{};
    
    FurnitureInstanceID m_nextFurnitureInstanceId{1};
    
    // containers
    std::vector<Tile>            m_floorTiles      {};
    std::vector<Tile>            m_northWallTiles  {};
    std::vector<Tile>            m_eastWallTiles   {};
    std::vector<PlacedFurniture> m_placedFurniture {};
    std::vector<PlacementCell>   m_placementCells  {};
    
    // placement cell index helper
    [[nodiscard]] auto placementCellIndex(PlacementPosition position) const -> std::size_t
    {
        return static_cast<std::size_t>(
            position.row * m_placementWidth + position.column
        );
    }
    [[nodiscard]] auto getIncrementedFurnitureID() -> FurnitureInstanceID { return m_nextFurnitureInstanceId++; }

    template<typename Fn>
    auto traverseCells(PlacementPosition origin, FurnitureFootprint footprint, Fn&& fn) -> void
    {

    }
};