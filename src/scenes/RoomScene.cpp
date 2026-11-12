#include "RoomScene.hpp"
#include "SDL3/SDL_events.h"
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


auto RoomScene::shutdown() -> void
{
    // Text objects must go before App shuts the text engine down.
    m_titleText.reset();
    m_textRenderer = nullptr;
    m_textureManager.clear();
}

auto RoomScene::update() -> void
{
    // frame time, so pan speed doesn't depend on frame rate
    const Uint64 now{SDL_GetTicksNS()};
    const float deltaSeconds{m_lastUpdateTicks == 0
        ? 0.0f
        : static_cast<float>(now - m_lastUpdateTicks) / static_cast<float>(SDL_NS_PER_SECOND)};
    m_lastUpdateTicks = now;

    // camera pan: arrow keys, held down
    const bool* keys{SDL_GetKeyboardState(nullptr)};
    SDL_FPoint direction{};
    if (keys[SDL_SCANCODE_LEFT])  direction.x -= 1.0f;
    if (keys[SDL_SCANCODE_RIGHT]) direction.x += 1.0f;
    if (keys[SDL_SCANCODE_UP])    direction.y -= 1.0f;
    if (keys[SDL_SCANCODE_DOWN])  direction.y += 1.0f;

    if (direction.x != 0.0f || direction.y != 0.0f)
    {
        // speed is in screen pixels; divide by zoom so it feels the same at every zoom level
        const float distance{k_cameraPanSpeed * deltaSeconds / static_cast<float>(m_camera.getZoomFactor())};
        m_camera.move({direction.x * distance, direction.y * distance});
    }
}

auto RoomScene::render(SDL_Renderer* renderer) const -> void
{
    int w{}, h{};
    SDL_GetRenderOutputSize(renderer, &w, &h); // get screen size (world)
    const SDL_FPoint screenSize{static_cast<float>(w), static_cast<float>(h)};

    drawTiles(renderer, screenSize);
    drawFurniture(renderer, screenSize);


    if (m_textRenderer)
        m_textRenderer->draw(m_titleText, 16.0f, 16.0f);
}

auto RoomScene::renderUI(SDL_Renderer* renderer, const UIManager& uiManager) const -> void
{
    uiManager.renderWrappers(renderer);
}

auto RoomScene::drawTiles(SDL_Renderer *renderer, SDL_FPoint screenSize) const -> void
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

        const auto screenDest{m_camera.rectToScreen(destination, screenSize)};
        floorTexture->render(renderer, &screenDest);

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
                    const auto northWallScreenDest{m_camera.rectToScreen(northWallDestination, screenSize)};
                    northWallTexture->render(renderer, &northWallScreenDest);
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

                    const auto eastWallScreenDest{m_camera.rectToScreen(eastWallDestination, screenSize)};
                    eastWallTexture->render(renderer, &eastWallScreenDest);
                }
            }
        }
    }
}

auto RoomScene::drawFurniture(SDL_Renderer* renderer, SDL_FPoint screenSize) const -> void
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

        const SDL_FPoint worldPos{
            Isometric::gridToWorld(
                RoomRendering::Constants::PlacementProjection,
                GridPosition{
                    furniture.position.column,
                    furniture.position.row
                }
            )
        };

        const float scale{definition.spriteScale};

        const SDL_FRect destination{
            worldPos.x + definition.drawOffset.x,
            worldPos.y + definition.drawOffset.y,
            texture->width() * scale,
            texture->height() * scale
        };

        const auto screenDest{m_camera.rectToScreen(destination, screenSize)};
        texture->render(renderer, &screenDest);
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
        // events carry no renderer, so look it up from the window the click came from
        int w{}, h{};
        SDL_GetRenderOutputSize(SDL_GetRenderer(SDL_GetWindowFromEvent(&event)), &w, &h);
        const SDL_FPoint screenSize{static_cast<float>(w), static_cast<float>(h)};

        const auto mousePos{
            HitTest::handleMouseButtonDown(event.button) };
        const auto cellPos {
            getPlacementPositionFromMouse(mousePos, screenSize) };
        const auto& furniture{
            Catalogue::Debug::getCurrentFurnitureDefinition(m_catalogue) };
        const auto placedID{
            m_room.tryPlaceFurniture(furniture, cellPos) };
    }

    // camera zoom: one step per wheel notch
    if(event.type == SDL_EVENT_MOUSE_WHEEL)
    {
        if(event.wheel.y > 0.0f)
            m_camera.zoomIn();
        else if(event.wheel.y < 0.0f)
            m_camera.zoomOut();
    }
}

auto RoomScene::getGridPositionFromMouse(SDL_FPoint mousePos, SDL_FPoint screenSize) const -> GridPosition
{
    const auto worldPos{m_camera.screenToWorld(mousePos, screenSize)};
    const auto gridCoordinates{
        Isometric::worldToGrid(
            RoomRendering::Constants::Projection
            ,worldPos)};
    return GridPosition {gridCoordinates};
}
auto RoomScene::getPlacementPositionFromMouse(SDL_FPoint mousePos, SDL_FPoint screenSize) const -> PlacementPosition
{
    const auto worldPos{m_camera.screenToWorld(mousePos, screenSize)};
    const auto cellCoordinates{
        Isometric::worldToGrid(
        RoomRendering::Constants::PlacementProjection
        ,worldPos)};
    return PlacementPosition {cellCoordinates};
}