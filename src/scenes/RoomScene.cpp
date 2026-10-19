#include "RoomScene.hpp"

auto RoomScene::generateFloor() -> void
{
    for (auto& tile : m_room.getFloorTiles())
    {
        // Initialize or modify the tile as needed
        
    }
}

auto RoomScene::render(SDL_Renderer* renderer) -> void
{
    for (auto [y, x] : std::views::cartesian_product(
         std::views::iota(0, m_room.getDepth()),
         std::views::iota(0, m_room.getWidth())))
    {
        const auto& tile = m_room.getTile(GridPosition{x, y});
        // Render tile.
    }
}

auto RoomScene::loadTextures(SDL_Renderer* renderer) -> void
{
    //will create asset manager which will load all textures
    m_woodFloorTileTexture.load(renderer, "assets\\pixel_salvaje\\environment\\Floor_Wall_Tiles_128\\Wall_L_128_WoodBright.png");
}