#include "RoomScene.hpp"
#include "debug.hpp"
#include "HitTest.hpp"
#include "Isometric.hpp"

#include <ranges>

namespace
{
    constexpr auto renderTexture = [](SDL_Renderer* renderer, Texture& texture, const SDL_FRect* destination){
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
        //test only
        if (furniture.uniqueID != FurnitureUniqueID::WoodenBed)
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


        //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        //SDL_RenderPoint(renderer, screenPos.x, screenPos.y);

        const auto& definition{Catalogue::Debug::getCurrentFurnitureDefinition(m_catalogue)};

        const float scale{definition.spriteScale};

        const SDL_FRect destination{
            screenPos.x + definition.drawOffset.x,
            screenPos.y + definition.drawOffset.y,
            m_woodenBedTexture.width() * scale,
            m_woodenBedTexture.height() * scale
        };

       renderTexture(renderer, m_woodenBedTexture, &destination);
    }
}

auto RoomScene::loadTextures(SDL_Renderer* renderer) -> void
{
    //will create asset manager which will load all textures
    const std::string basePath{SDL_GetBasePath()};
    m_woodFloorTileTexture.load(renderer, basePath + "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_Japan_2.png");
    m_northWallTileTexture.load(renderer, basePath + "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_BlueSea.png");
    m_eastWallTileTexture.load(renderer, basePath + "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_BlueSea.png");
    m_woodenBedTexture.load(renderer, basePath + "assets/pixel_salvaje/themed_sets/Bedroom/Bed_E_4.png");
}

auto RoomScene::handleEvent(const SDL_Event& event) -> void
{
    if(event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_TAB)
    {
        Catalogue::Debug::cycleFurnitureCatalogue(m_catalogue);
    }
    if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN &&
       event.button.button == SDL_BUTTON_LEFT)
    {
        const auto mousePos{ HitTest::handleMouseButtonDown(event.button) };
        const auto cellPos { getPlacementPositionFromMouse(mousePos) };
        const auto& furniture{
            Catalogue::Debug::getCurrentFurnitureDefinition(m_catalogue)
        };
        const auto placedID{
            m_room.tryPlaceFurniture(furniture, cellPos)
        };
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