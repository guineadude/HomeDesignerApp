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
}

auto RoomScene::render(SDL_Renderer* renderer) -> void
{
    renderTiles(renderer);
    renderFurniture(renderer);
}

auto RoomScene::renderTiles(SDL_Renderer *renderer) -> void
{
    const float floorSpriteWidth{m_woodFloorTileTexture.width()};
    const float floorSpriteHeight{m_woodFloorTileTexture.height()};
    const float northWallSpriteWidth{m_northWallTileTexture.width()};
    const float northWallSpriteHeight{m_northWallTileTexture.height()};
    const float eastWallSpriteWidth{m_eastWallTileTexture.width()};
    const float eastWallSpriteHeight{m_eastWallTileTexture.height()};
    
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
        renderTexture(renderer, m_woodFloorTileTexture, &destination);

        if (row == 0)
        {
            const SDL_FRect northWallDestination{
                destination.x + RoomRendering::Constants::NorthWallOffsetX,
                destination.y + RoomRendering::Constants::WallOffsetY,
                northWallSpriteWidth,
                northWallSpriteHeight
            };

            renderTexture(renderer, m_northWallTileTexture, &northWallDestination);
        }
        if (column == 0)
        {
            const SDL_FRect eastWallDestination{
                destination.x + RoomRendering::Constants::EastWallOffsetX,
                destination.y + RoomRendering::Constants::WallOffsetY,
                eastWallSpriteWidth,
                eastWallSpriteHeight
            };

            renderTexture(renderer, m_eastWallTileTexture, &eastWallDestination);
        }
    }
}

auto RoomScene::renderFurniture(SDL_Renderer* renderer) -> void
{
    for (const auto& furniture : m_room.getPlacedFurniture())
    {
        const auto& definition{m_catalogue.getDefinition(furniture.uniqueID)};

        const Texture* texture{};
        switch (furniture.uniqueID)
        {
        case FurnitureUniqueID::WoodenBed:
            texture = &m_woodenBedTexture;
            break;
        case FurnitureUniqueID::WoodenCupboard:
            texture = &m_woodenCupboardTexture;
            break;
        case FurnitureUniqueID::BedsideTable:
            texture = &m_bedsideTableTexture;
            break;
        case FurnitureUniqueID::WoodenTable:
            texture = &m_woodenTableTexture;
            break;
        case FurnitureUniqueID::PottedPlant:
            texture = &m_pottedPlantTexture;
            break;
        default:
            throw std::out_of_range("Furniture ID has no texture");
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
    const char* basePath{SDL_GetBasePath()};

    if (!basePath)
    {
        Core::Debug::log(
            "Failed to get application base path: ", SDL_GetError());
        return false;
    }

    struct TextureAsset
    {
        Texture& texture;
        const char* relativePath;
    };

    const TextureAsset assets[]{
        {m_woodFloorTileTexture,
         "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_Japan_2.png"},
        {m_northWallTileTexture,
         "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_BlueSea.png"},
        {m_eastWallTileTexture,
         "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_BlueSea.png"},
        {m_woodenBedTexture,
         "assets/pixel_salvaje/themed_sets/Bedroom/Bed_E_4.png"},
        {m_woodenCupboardTexture,
         "assets/pixel_salvaje/themed_sets/Office/Office_Wood_Closet_Ani/Office_Wood_Closet.png"},
        {m_bedsideTableTexture,
         "assets/pixel_salvaje/themed_sets/Bedroom/Night_Table_Tile.png"},
        {m_woodenTableTexture,
         "assets/pixel_salvaje/furniture/Tables/Table_10.png"},
        {m_pottedPlantTexture,
         "assets/pixel_salvaje/decorations/Plants/Plant_1.png"}
    };

    for (const auto& asset : assets)
    {
        const std::string fullPath{
              std::string{basePath} + asset.relativePath
        };

        if (!asset.texture.load(renderer, fullPath))
        {
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