#include "RoomScene.hpp"

auto RoomScene::render(SDL_Renderer* renderer) -> void
{
    constexpr float floorTileStepX{32.0f};//64
    constexpr float floorTileStepY{16.0f};//32
    constexpr float northWallOffsetX{16.0f};//32
    constexpr float westWallOffsetX{-16.0f};//-32
    constexpr float wallOffsetY{-23.5f};//-47
    constexpr float spriteTopPadding{18.0f};//36
    constexpr float originX{640.0f};//640
    constexpr float originY{200.0f};//200

    const float spriteWidth{m_woodFloorTileTexture.width()};
    const float spriteHeight{m_woodFloorTileTexture.height()};

    auto floorDestination = [&](int depth, int width){
        const float screenX{
            originX + static_cast<float>(width - depth) * floorTileStepX};
        const float screenY{
            originY + static_cast<float>(width + depth) * floorTileStepY};

        return SDL_FRect{
            screenX - spriteWidth * .5f,
            screenY - spriteTopPadding,
            spriteWidth,
            spriteHeight
        };
    };

    // Floors first so later floor tiles can't cover walls
    for (auto [depth, width] : std::views::cartesian_product(
             std::views::iota(0, m_room.getDepth()),
             std::views::iota(0, m_room.getWidth())))
    {
        const SDL_FRect destination{floorDestination(depth, width)};

        SDL_RenderTexture(
            renderer,
            m_woodFloorTileTexture.get(),
            nullptr,
            &destination);
    }

    // With this projection the back walls are the depth == 0 row (upper right
    // edge) and the width == 0 column (upper left edge)
    for (auto [depth, width] : std::views::cartesian_product(
             std::views::iota(0, m_room.getDepth()),
             std::views::iota(0, m_room.getWidth())))
    {
        const SDL_FRect floor{floorDestination(depth, width)};

        if (depth == 0)
        {
            const SDL_FRect northWallDestination{
                floor.x + northWallOffsetX,
                floor.y + wallOffsetY,
                spriteWidth,
                spriteHeight
            };

            SDL_RenderTexture(
                renderer,
                m_northWallTileTexture.get(),
                nullptr,
                &northWallDestination);
        }

        if (width == 0)
        {
            const SDL_FRect westWallDestination{
                floor.x + westWallOffsetX,
                floor.y + wallOffsetY,
                spriteWidth,
                spriteHeight
            };

            SDL_RenderTexture(
                renderer,
                m_westWallTileTexture.get(),
                nullptr,
                &westWallDestination);
        }
    }
}

auto RoomScene::loadTextures(SDL_Renderer* renderer) -> void
{
    //will create asset manager which will load all textures
    const std::string basePath{SDL_GetBasePath()};
    m_woodFloorTileTexture.load(renderer, basePath + "assets/pixel_salvaje/environment/Floor_Wall_Tiles_64/Floor_64_WoodBright.png");
    m_northWallTileTexture.load(renderer, basePath + "assets/pixel_salvaje/environment/Floor_Wall_Tiles_64/Wall_R_64_WoodBright.png");
    m_westWallTileTexture.load(renderer, basePath + "assets/pixel_salvaje/environment/Floor_Wall_Tiles_64/Wall_L_64_WoodBright.png");
}