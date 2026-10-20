#include "RoomScene.hpp"

namespace 
{
    constexpr float spriteScale{1.0f};

    // Rendering step sizes and offsets for floor and wall tiles
    constexpr float floorTileStepX{64.0f * spriteScale};
    constexpr float floorTileStepY{32.0f * spriteScale};
    constexpr float northWallOffsetX{32.0f * spriteScale};
    constexpr float eastWallOffsetX{-32.0f * spriteScale};
    constexpr float wallOffsetY{-47.0f * spriteScale};
    constexpr float spriteTopPadding{36.0f * spriteScale};

    // Origin point for rendering calculations
    constexpr float originX{640.0f};
    constexpr float originY{200.0f};

    constexpr auto renderTexture = [](SDL_Renderer* renderer, Texture& texture, const SDL_FRect* destination){
        SDL_RenderTexture(renderer, texture.get(), nullptr, destination);
    };
}

auto RoomScene::render(SDL_Renderer* renderer) -> void
{
    const float floorSpriteWidth{m_woodFloorTileTexture.width() * spriteScale};
    const float floorSpriteHeight{m_woodFloorTileTexture.height() * spriteScale};
    const float northWallSpriteWidth{m_northWallTileTexture.width() * spriteScale};
    const float northWallSpriteHeight{m_northWallTileTexture.height() * spriteScale};
    const float eastWallSpriteWidth{m_eastWallTileTexture.width() * spriteScale};
    const float eastWallSpriteHeight{m_eastWallTileTexture.height() * spriteScale};

    //calculate the destination rectangle for floor tiles
    auto floorDestination = [&](int depth, int width){
        const float screenX{
            originX + static_cast<float>(width - depth) * floorTileStepX};
        const float screenY{
            originY + static_cast<float>(width + depth) * floorTileStepY};

        return SDL_FRect{
            screenX - floorSpriteWidth * .5f,
            screenY - spriteTopPadding,
            floorSpriteWidth,
            floorSpriteHeight
        };
    };

    for (auto [depth, width] : std::views::cartesian_product(
             std::views::iota(0, m_room.getDepth()),
             std::views::iota(0, m_room.getWidth())))
    {
        
        const SDL_FRect destination{floorDestination(depth, width)};
        renderTexture(renderer, m_woodFloorTileTexture, &destination);

        if (depth == 0)
        {
            const SDL_FRect northWallDestination{
                destination.x + northWallOffsetX,
                destination.y + wallOffsetY,
                northWallSpriteWidth,
                northWallSpriteHeight
            };

            renderTexture(renderer, m_northWallTileTexture, &northWallDestination);
        }
        if (width == 0)
        {
            const SDL_FRect eastWallDestination{
                destination.x + eastWallOffsetX,
                destination.y + wallOffsetY,
                eastWallSpriteWidth,
                eastWallSpriteHeight
            };

            renderTexture(renderer, m_eastWallTileTexture, &eastWallDestination);
        }
    }
}

auto RoomScene::loadTextures(SDL_Renderer* renderer) -> void
{
    //will create asset manager which will load all textures
    const std::string basePath{SDL_GetBasePath()};
    m_woodFloorTileTexture.load(renderer, basePath + "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_BlueSea.png");
    m_northWallTileTexture.load(renderer, basePath + "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_BlueSea.png");
    m_eastWallTileTexture.load(renderer, basePath + "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_BlueSea.png");
}