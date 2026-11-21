#pragma once

#include <algorithm>
#include <optional>
#include <vector>
#include <ranges>

#include "room/Tile.hpp"
#include "room/RoomBuildInstructions.hpp"
#include "furniture/FurnitureCatalogue.hpp"
#include "room/placement/GridPosition.hpp"
#include "room/placement/PlacementCell.hpp"
#include "room/placement/PlacementGrid.hpp"
#include "furniture/FurnitureFootprint.hpp"
#include "furniture/FurnitureInstanceID.hpp"
#include "furniture/PlacedFurniture.hpp"

class Room 
{
public:
    explicit Room(const RoomBuildInstructions& instructions)
    : m_width{instructions.width}
    , m_depth{instructions.depth}
    , m_placementWidth{m_width * PlacementGrid::cellsPerTileAxis}
    , m_placementDepth{m_depth * PlacementGrid::cellsPerTileAxis}
    , m_floorTiles{ static_cast<std::size_t>(m_width * m_depth), FloorTile{instructions.floorType} }
    , m_northWallTiles{ static_cast<std::size_t>(m_northWallHeight * m_width), WallTile{instructions.northWallType} }
    , m_eastWallTiles{ static_cast<std::size_t>(m_eastWallHeight * m_depth), WallTile{instructions.eastWallType} }
    , m_placementCells{ static_cast<std::size_t>(m_placementWidth * m_placementDepth) }
    {}

    // Places the furniture listed in the instructions; entries that don't fit are skipped.
    auto applyFurniture(const RoomBuildInstructions& instructions, const FurnitureCatalogue& catalogue) -> void;

    //getters
    [[nodiscard]] auto getWidth() const -> int { return m_width; }
    [[nodiscard]] auto getDepth() const -> int { return m_depth; }
    [[nodiscard]] auto getNorthWallHeight() const -> int { return m_northWallHeight; }
    [[nodiscard]] auto getEastWallHeight() const -> int { return m_eastWallHeight; }
    [[nodiscard]] auto getPlacementWidth() const -> int { return m_placementWidth; }
    [[nodiscard]] auto getPlacementDepth() const -> int { return m_placementDepth; }
    [[nodiscard]] auto shouldPlaceWall(int row, int col) const -> bool { return row == 0 || col == 0; }
    [[nodiscard]] auto isRightWall(int col) const -> bool { return col == 0; }
    [[nodiscard]] auto isTopWall(int row) const -> bool { return row == 0; }

    //floor tiles getters
    [[nodiscard]] auto getFloorTile(const GridPosition& position) -> FloorTile& 
    { 
        return m_floorTiles[position.row * m_width + position.column]; 
    }
    [[nodiscard]] auto getFloorTile(const GridPosition& position) const -> const FloorTile& 
    {
        return m_floorTiles[position.row * m_width + position.column]; 
    }
    [[nodiscard]] auto getFloorTiles() -> std::vector<FloorTile>& { return m_floorTiles; }
    [[nodiscard]] auto getFloorTiles() const -> const std::vector<FloorTile>& { return m_floorTiles; }
    
    //wall tiles getters
    [[nodiscard]] auto getEastWallTile(const GridPosition& position) -> WallTile& 
    {
        return m_eastWallTiles[position.row * m_eastWallHeight + position.column];
    }
    [[nodiscard]] auto getEastWallTile(const GridPosition& position) const -> const WallTile& 
    {
        return m_eastWallTiles[position.row * m_eastWallHeight + position.column];
    }
    [[nodiscard]] auto getNorthWallTile(const GridPosition& position) -> WallTile& 
    {
        return m_northWallTiles[position.row * m_northWallHeight + position.column];
    }
    [[nodiscard]] auto getNorthWallTile(const GridPosition& position) const -> const WallTile& 
    {
        return m_northWallTiles[position.row * m_northWallHeight + position.column];
    }
    [[nodiscard]] auto getNorthWallTiles() -> std::vector<WallTile>& { return m_northWallTiles; }
    [[nodiscard]] auto getNorthWallTiles() const -> const std::vector<WallTile>& { return m_northWallTiles; }
    [[nodiscard]] auto getEastWallTiles() -> std::vector<WallTile>& { return m_eastWallTiles; }
    [[nodiscard]] auto getEastWallTiles() const -> const std::vector<WallTile>& { return m_eastWallTiles; }
    
//furniture
    [[nodiscard]] auto getPlacedFurniture() const -> const std::vector<PlacedFurniture>& { return m_placedFurniture; }
    [[nodiscard]] auto tryPlaceFurniture(const FurnitureDefinition& furniture, PlacementPosition position) -> std::optional<FurnitureInstanceID>;
    [[nodiscard]] auto canPlaceFurniture(PlacementPosition position, FurnitureFootprint footprint) const -> bool;
    auto occupyCells(PlacementPosition position, FurnitureFootprint footprint, FurnitureInstanceID instanceID) -> void;
    auto sortPlacedFurniture() -> void;
    
private:
    // room dimensions and wall heights
    int m_width {}, m_depth {}, m_northWallHeight{1}, m_eastWallHeight{1};
    // placement grid size
    int m_placementWidth{}, m_placementDepth{};
    
    FurnitureInstanceID m_nextFurnitureInstanceId{1};
    
    // containers
    std::vector<FloorTile>       m_floorTiles      {};
    std::vector<WallTile>        m_northWallTiles  {};
    std::vector<WallTile>        m_eastWallTiles   {};
    std::vector<PlacedFurniture> m_placedFurniture {};
    std::vector<PlacementCell>   m_placementCells  {};
    
    // placement cell index helper
    [[nodiscard]] auto placementCellIndex(PlacementPosition position) const -> std::size_t
    {
        return static_cast<std::size_t>(
            position.row * m_placementWidth + position.column
        );
    }
    [[nodiscard]] static auto footprintCells(PlacementPosition position, FurnitureFootprint footprint)
    {
        return std::views::cartesian_product(
                std::views::iota(0, footprint.depth),
                std::views::iota(0, footprint.width))
            | std::views::transform([position](auto rc) {
                auto [r, c] = rc;
                return PlacementPosition{position.column + c, position.row + r};
            });
    }

    template <typename Fn>
    static auto forEachFootprintCell(PlacementPosition p, FurnitureFootprint f, Fn&& fn) -> void
    {
        std::ranges::for_each(footprintCells(p, f), fn);
    }

    template <typename Pred>
    [[nodiscard]] static auto allFootprintCells(PlacementPosition p, FurnitureFootprint f, Pred&& pred) -> bool
    {
        return std::ranges::all_of(footprintCells(p, f), pred);
    }

    auto getNextFurnitureID() -> FurnitureInstanceID { return m_nextFurnitureInstanceId++; }
};