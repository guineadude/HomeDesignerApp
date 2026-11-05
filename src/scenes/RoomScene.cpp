#include "RoomScene.hpp"
#include "debug.hpp"
#include "HitTest.hpp"
#include "Isometric.hpp"

#include <cstddef>
#include <ranges>
#include <stdexcept>

namespace
{
    constexpr auto renderTexture = [](SDL_Renderer* renderer, const Texture& texture, const SDL_FRect* destination){
        SDL_RenderTexture(renderer, texture.get(), nullptr, destination);
    };
    
    constexpr char floorTexturePath[]{
        "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_Japan_2.png"
    };

    constexpr char northWallTexturePath[]{
        "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_BlueSea.png"
    };

    constexpr char eastWallTexturePath[]{
        "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_BlueSea.png"
    };
}

auto RoomScene::shutdown() -> void
{
    m_textureManager.clear();
}

auto RoomScene::update() -> void
{
}

auto RoomScene::render(SDL_Renderer* renderer) const -> void
{
    renderTiles(renderer);
    renderFurniture(renderer);
}

auto RoomScene::renderTiles(SDL_Renderer *renderer) const -> void
{
    const auto* floorTexture{m_textureManager.get(floorTexturePath)};
    const auto* northWallTexture{m_textureManager.get(northWallTexturePath)};
    const auto* eastWallTexture{m_textureManager.get(eastWallTexturePath)};

    if (!floorTexture || !northWallTexture || !eastWallTexture)
    {
        return;
    }

    const float floorSpriteWidth{floorTexture->width()};
    const float floorSpriteHeight{floorTexture->height()};
    const float northWallSpriteWidth{northWallTexture->width()};
    const float northWallSpriteHeight{northWallTexture->height()};
    const float eastWallSpriteWidth{eastWallTexture->width()};
    const float eastWallSpriteHeight{eastWallTexture->height()};
    
    //calculate the destination rectangle for floor tiles
    auto floorDestination = [&](int row, int column, float spriteWidth, float spriteHeight){
        const SDL_FPoint screenPos{
            Isometric::gridToScreen(
                {
                    {RoomRendering::Constants::OriginX, RoomRendering::Constants::OriginY},
                    Isometric::Constants::TileStepX,
                    Isometric::Constants::TileStepY
                },
                {column, row})
        };

        return SDL_FRect{
            screenPos.x - spriteWidth * .5f,
            screenPos.y - RoomRendering::Constants::FloorSpriteTopPadding,
            spriteWidth,
            spriteHeight
        };
    };

    for (auto [row, column] : std::views::cartesian_product(
            std::views::iota(0, m_room.getDepth()),
                        std::views::iota(0, m_room.getWidth())))
    {
        
        const SDL_FRect destination{ floorDestination(row, column, floorSpriteWidth, floorSpriteHeight) };
        renderTexture(renderer, *floorTexture, &destination);

        if (row == 0)
        {
            const SDL_FRect northWallDestination{
                destination.x + RoomRendering::Constants::NorthWallOffsetX,
                destination.y + RoomRendering::Constants::WallOffsetY,
                northWallSpriteWidth,
                northWallSpriteHeight
            };

            renderTexture(renderer, *northWallTexture, &northWallDestination);
        }
        if (column == 0)
        {
            const SDL_FRect eastWallDestination{
                destination.x + RoomRendering::Constants::EastWallOffsetX,
                destination.y + RoomRendering::Constants::WallOffsetY,
                eastWallSpriteWidth,
                eastWallSpriteHeight
            };

            renderTexture(renderer, *eastWallTexture, &eastWallDestination);
        }
    }
}

auto RoomScene::renderFurniture(SDL_Renderer* renderer) const -> void
{
    for (const auto& furniture : m_room.getPlacedFurniture())
    {
        const auto& definition{
            m_catalogue.getDefinitionByID(furniture.uniqueID)
        };

        const auto* texture{
            m_textureManager.get(definition.texturePath)
        };

        if (!texture)
        {
            continue;
        }

        const SDL_FPoint screenPos{
            Isometric::gridToScreen(
                RoomRendering::Constants::placementProjection,
                GridPosition{
                    furniture.position.column,
                    furniture.position.row
                }
            )
        };

        const float scale{definition.spriteScale};

        const SDL_FRect destination{
            screenPos.x + definition.drawOffset.x,
            screenPos.y + definition.drawOffset.y,
            texture->width() * scale,
            texture->height() * scale
        };

        renderTexture(renderer, *texture, &destination);
    }
}

auto RoomScene::loadTextures(SDL_Renderer* renderer) -> bool
{
     m_textureManager.clear();

    const char* tilePaths[]{
        floorTexturePath,
        northWallTexturePath,
        eastWallTexturePath
    };

    for (const auto* path : tilePaths)
    {
        if (!m_textureManager.load(renderer, path))
        {
            Core::Debug::log(
                "Failed to load texture: ", path,
                " — ", SDL_GetError());

            return false;
        }
    }
    for (std::size_t index{}; index < m_catalogue.size(); ++index)
    {
        const auto& definition{m_catalogue.getDefinitionAt(index)};

        if (!m_textureManager.load(renderer, definition.texturePath))
        {
            Core::Debug::log(
                "Failed to load texture: ", definition.texturePath,
                " — ", SDL_GetError());

            return false;
        }
    }

    return true;
}

auto RoomScene::handleEvent(const SDL_Event& event) -> void
{
    if(event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_TAB)
    {
        Catalogue::Debug::cycleFurnitureCatalogue(m_catalogue);
    }
    if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT)
    {
        const auto mousePos{ 
            HitTest::handleMouseButtonDown(event.button) };
        const auto cellPos { 
            getPlacementPositionFromMouse(mousePos) };
        const auto& furniture{
            Catalogue::Debug::getCurrentFurnitureDefinition(m_catalogue) };
        const auto placedID{
            m_room.tryPlaceFurniture(furniture, cellPos) };
    }
}

auto RoomScene::getGridPositionFromMouse(SDL_FPoint mousePos) const -> GridPosition
{
    const auto gridCoordinates{
        Isometric::screenToGrid(
            RoomRendering::Constants::Projection
            ,mousePos)};
    return GridPosition {gridCoordinates};
}
auto RoomScene::getPlacementPositionFromMouse(SDL_FPoint mousePos) const -> PlacementPosition
{
    const auto cellCoordinates{
        Isometric::screenToGrid(
        RoomRendering::Constants::placementProjection
        ,mousePos)};
    return PlacementPosition {cellCoordinates};
}