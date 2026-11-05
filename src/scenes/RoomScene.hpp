#pragma once

#include <SDL3/SDL.h>

#include "debug.hpp"

#include "furniture/FurnitureCatalogue.hpp"
#include "room/placement/PlacementGrid.hpp"
#include "room/Room.hpp"
#include "core/Isometric.hpp"
#include "graphics/Texture.hpp"
#include "graphics/TextureManager.hpp"

class RoomScene
{
public:
    RoomScene(Room& room)
        : m_room(room)
    {}

    [[nodiscard]] auto loadTextures(SDL_Renderer* renderer) -> bool;
    auto update() -> void;
    auto render(SDL_Renderer* renderer) const -> void;
    auto handleEvent(const SDL_Event& event)-> void;
    auto shutdown() -> void;

    auto getRoom() -> Room& { return m_room; }
    auto getRoom() const -> const Room& { return m_room; }

    //furniture + catalogue controls
    auto cycleFurnitureCatalogue() -> void { Catalogue::Debug::cycleFurnitureCatalogue(m_catalogue); }
    auto updatePlacementPreview() -> void; //TODO add preview logic
    auto confirmPlacement() -> void; //TODO add logic
    auto cancelPlacement() -> void; //TODO add logic

private:
    Room& m_room;
    FurnitureCatalogue m_catalogue {};
    TextureManager m_textureManager {};
    Texture m_woodFloorTileTexture {};
    Texture m_northWallTileTexture {};
    Texture m_eastWallTileTexture  {};
    Texture m_woodenBedTexture {};
    Texture m_woodenCupboardTexture {};
    Texture m_bedsideTableTexture {};
    Texture m_woodenTableTexture {};
    Texture m_pottedPlantTexture {};

    // convert mouse to different grid types
    [[nodiscard]] auto getGridPositionFromMouse(SDL_FPoint mousePos) const -> GridPosition;
    [[nodiscard]] auto getPlacementPositionFromMouse(SDL_FPoint mousePos) const -> PlacementPosition;

    // render helpers
    auto renderTiles(SDL_Renderer* renderer) const -> void;
    auto renderFurniture(SDL_Renderer* renderer) const -> void;
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
    inline constexpr Isometric::Projection placementProjection{
    RoomRendering::Constants::Projection.origin,
    Isometric::Constants::TileStepX / PlacementGrid::cellsPerTileAxis,
    Isometric::Constants::TileStepY / PlacementGrid::cellsPerTileAxis
};
}
