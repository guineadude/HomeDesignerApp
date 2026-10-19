#include "RoomScene.hpp"

auto RoomScene::render(SDL_Renderer* renderer) -> void
{
    constexpr float tileStepX{64.0f};
    constexpr float tileStepY{32.0f};
    constexpr float spriteTopPadding{36.0f};
    constexpr float originX{640.0f};
    constexpr float originY{200.0f};

    const float spriteWidth{m_woodFloorTileTexture.width()};
    const float spriteHeight{m_woodFloorTileTexture.height()};

    auto isWallTile = [](int depth, int width, const Room& room){
        return depth == 0 || width == room.getWidth() - 1;
    };

    for (auto [depth, width] : std::views::cartesian_product(
             std::views::iota(0, m_room.getDepth()),
             std::views::iota(0, m_room.getWidth())))
        {
        const float screenX{
            originX + static_cast<float>(width - depth) * tileStepX};
        const float screenY{
            originY + static_cast<float>(width + depth) * tileStepY};

        const SDL_FRect destination{
            screenX - spriteWidth * .5f,
            screenY - spriteTopPadding,
            spriteWidth,
            spriteHeight
        };

        SDL_RenderTexture(
            renderer,
            m_woodFloorTileTexture.get(),
            nullptr,
            &destination);
    }
}

auto RoomScene::loadTextures(SDL_Renderer* renderer) -> void
{
    //will create asset manager which will load all textures
    const std::string basePath{SDL_GetBasePath()};
    m_woodFloorTileTexture.load(renderer, basePath + "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_WoodBright.png");
}