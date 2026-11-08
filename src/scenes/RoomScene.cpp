#include "RoomScene.hpp"
#include "debug.hpp"
#include "HitTest.hpp"
#include "Isometric.hpp"

#include <cstddef>
#include <ranges>
#include <set>
#include <string>

#include "graphics/Texture.hpp"
#include "room/FloorTextures.hpp"
#include "room/WallTextures.hpp"

namespace
{
    constexpr auto renderTexture = [](SDL_Renderer* renderer, const Texture& texture, const SDL_FRect* destination){
        SDL_RenderTexture(renderer, texture.get(), nullptr, destination);
    };
}

auto RoomScene::shutdown() -> void
{
    // Text objects must go before App shuts the text engine down.
    m_titleText.reset();
    m_textRenderer = nullptr;
    m_textureManager.clear();
}

auto RoomScene::update() -> void
{
}

auto RoomScene::render(SDL_Renderer* renderer) const -> void
{
    drawTiles(renderer);
    drawFurniture(renderer);

    if (m_textRenderer)
        m_textRenderer->draw(m_titleText, 16.0f, 16.0f);
}

auto RoomScene::drawTiles(SDL_Renderer *renderer) const -> void
{    
    for (auto [row, column] : std::views::cartesian_product(
        std::views::iota(0, m_room.getDepth()),
        std::views::iota(0, m_room.getWidth())))
    {
        const auto floorType{m_room.getFloorTile(GridPosition{column, row}).type};
        const auto* floorTexture{m_textureManager.get(FloorTextures::pathFor(floorType))};

        if (!floorTexture)
            continue;

        const auto destination{
            RoomRendering::Constants::floorDestination
                (row, column, floorTexture->width(), floorTexture->height())
        };

        renderTexture(renderer, *floorTexture, &destination);

        if(m_room.shouldPlaceWall(row, column))
        {            
            if(m_room.isTopWall(row))
            {
                const auto northWallType{m_room.getNorthWallTile(GridPosition{column, 0}).type};
                const auto* northWallTexture{m_textureManager.get(WallTextures::rightPathFor(northWallType))};

                if (northWallTexture)
                {
                    const SDL_FRect northWallDestination{
                        destination.x + RoomRendering::Constants::NorthWallOffsetX,
                        destination.y + RoomRendering::Constants::WallOffsetY,
                        northWallTexture->width(),
                        northWallTexture->height()
                    };
                    const auto* tex { northWallTexture };
                    renderTexture(renderer, *tex, &northWallDestination);
                }
            }
            if(m_room.isRightWall(column))
            {
                const auto eastWallType{m_room.getEastWallTile(GridPosition{0, row}).type};
                const auto* eastWallTexture{m_textureManager.get(WallTextures::leftPathFor(eastWallType))};
                if (eastWallTexture)
                {
                    const SDL_FRect eastWallDestination{
                        destination.x + RoomRendering::Constants::EastWallOffsetX,
                        destination.y + RoomRendering::Constants::WallOffsetY,
                        eastWallTexture->width(),
                        eastWallTexture->height()
                    };

                    const auto* tex { eastWallTexture };
                    renderTexture(renderer, *tex, &eastWallDestination);
                }
            }
        }
    }
}

auto RoomScene::drawFurniture(SDL_Renderer* renderer) const -> void
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
            continue;

        const SDL_FPoint screenPos{
            Isometric::gridToScreen(
                RoomRendering::Constants::PlacementProjection,
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

auto RoomScene::loadText(TextRenderer& textRenderer) -> bool
{
    m_textRenderer = &textRenderer;

    m_titleText = m_textRenderer->createText("Catalogue", 30.0f, SDL_Color{58, 58, 80, 255});
    if (!m_titleText)
    {
        Core::Debug::log("Failed to create title text");
        return false;
    }

    return true;
}

auto RoomScene::loadTextures(SDL_Renderer* renderer, TextRenderer& textRenderer) -> bool
{
    m_textureManager.clear();

    if (!loadText(textRenderer))
        return false;

    if(!loadTileTextures(renderer))
        return false;

    if(!loadFurnitureTextures(renderer))
        return false;

    return true;
}

auto RoomScene::loadTileTextures(SDL_Renderer *renderer) -> bool
{
    // load floor and wall textures
    std::set<std::string> tilePaths;
    for (const auto& tile : m_room.getFloorTiles())
    {
        tilePaths.emplace(FloorTextures::pathFor(tile.type));
    }
    for (const auto& tile : m_room.getNorthWallTiles())
    {
        tilePaths.emplace(WallTextures::rightPathFor(tile.type));
    }
    for (const auto& tile : m_room.getEastWallTiles())
    {
        tilePaths.emplace(WallTextures::leftPathFor(tile.type));
    }
    for (const auto& path : tilePaths)
    {
        if (!m_textureManager.load(renderer, path))
        {
            Core::Debug::log(
                "Failed to load texture: ", path,
                " — ", SDL_GetError());

            return false;
        }
    }

    return true;
}

auto RoomScene::loadFurnitureTextures(SDL_Renderer *renderer) -> bool
{
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
        RoomRendering::Constants::PlacementProjection
        ,mousePos)};
    return PlacementPosition {cellCoordinates};
}