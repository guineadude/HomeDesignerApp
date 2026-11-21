#pragma once

#include <SDL3/SDL.h>

#include "debug/Debug.hpp"
#include "furniture/FurnitureCatalogue.hpp"
#include "room/placement/PlacementGrid.hpp"
#include "room/Room.hpp"
#include "core/Isometric.hpp"
#include "graphics/TextureManager.hpp"
#include "ui/UIManager.hpp"
#include "scenes/Camera.hpp"

class RoomScene
{
public:
    RoomScene(Room& room, const RoomBuildInstructions& instructions)
        : m_room(room)
    {
        m_room.applyFurniture(instructions, m_catalogue);
        m_camera.setCenter({640.f, 360.f}); // half of 1280x720: zoom 1 matches the old layout exactly
    }

    [[nodiscard]] auto loadTextures(SDL_Renderer* renderer) -> bool;
    auto update() -> void;
    auto render(SDL_Renderer* renderer) const -> void;
    auto renderUI(SDL_Renderer* renderer, const UIManager& uiManager) const -> void;
    auto handleEvent(const SDL_Event& event)-> void;
    auto shutdown() -> void;

    // accessors for room
    auto getRoom() -> Room& { return m_room; }
    auto getRoom() const -> const Room& { return m_room; }

    //furniture + catalogue controls
    auto cycleFurnitureCatalogue() -> void { Catalogue::Debug::cycleFurnitureCatalogue(m_catalogue); }
    auto updatePlacementPreview() -> void; //TODO add preview logic
    auto confirmPlacement() -> void; //TODO add logic
    auto cancelPlacement() -> void; //TODO add logic

private:
    Room& m_room;
    Camera m_camera {};
    FurnitureCatalogue m_catalogue {};
    TextureManager m_textureManager {};

    // camera panning
    static constexpr float k_cameraPanSpeed {600.0f}; // screen pixels per second
    Uint64 m_lastUpdateTicks {0};

    // convert mouse (screen space) to different grid types, via the camera
    [[nodiscard]] auto getGridPositionFromMouse(SDL_FPoint mousePos, SDL_FPoint screenSize) const -> GridPosition;
    [[nodiscard]] auto getPlacementPositionFromMouse(SDL_FPoint mousePos, SDL_FPoint screenSize) const -> PlacementPosition;

    // render helpers
    auto drawTiles(SDL_Renderer* renderer, SDL_FPoint screenSize) const -> void;
    auto drawFurniture(SDL_Renderer* renderer, SDL_FPoint screenSize) const -> void;

    // texture loaders
    auto loadTileTextures(SDL_Renderer* renderer) -> bool;
    auto loadFurnitureTextures(SDL_Renderer* renderer) -> bool;
};

namespace RoomRendering::Constants
{
    inline constexpr float OriginX{640.0f};
    inline constexpr float OriginY{200.0f};
    inline constexpr float NorthWallOffsetX{32.0f};
    inline constexpr float EastWallOffsetX{-32.0f};
    inline constexpr float WallOffsetY{-47.0f};
    inline constexpr float FloorSpriteTopPadding{36.0f};

    inline constexpr Isometric::Projection Projection{
        RoomRendering::Constants::OriginX,
        RoomRendering::Constants::OriginY,
        Isometric::Constants::TileStepX,
        Isometric::Constants::TileStepY
    };
    inline constexpr Isometric::Projection PlacementProjection{
        RoomRendering::Constants::Projection.origin,
        Isometric::Constants::TileStepX / PlacementGrid::cellsPerTileAxis,
        Isometric::Constants::TileStepY / PlacementGrid::cellsPerTileAxis
    };
    constexpr auto floorDestination = [](int row, int column, float spriteWidth, float spriteHeight)
    {
        const SDL_FPoint worldPos{
            Isometric::gridToWorld(
                {
                    {RoomRendering::Constants::OriginX, RoomRendering::Constants::OriginY},
                    Isometric::Constants::TileStepX,
                    Isometric::Constants::TileStepY
                },
                {column, row})
        };

        return SDL_FRect{
            worldPos.x - spriteWidth * .5f,
            worldPos.y - RoomRendering::Constants::FloorSpriteTopPadding,
            spriteWidth,
            spriteHeight
        };
    };

}
