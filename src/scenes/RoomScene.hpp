#pragma once

#include <SDL3/SDL.h>

#include "debug.hpp"
#include "FurnitureCatalogue.hpp"
#include "Room.hpp"
#include "Texture.hpp"
#include "HitTest.hpp"
#include "Isometric.hpp"

class RoomScene
{
    public:
    RoomScene(Room& room)
        : m_room(room)
    {}

    auto loadTextures(SDL_Renderer* renderer) -> void;
    auto render(SDL_Renderer* renderer) -> void;
    auto handleEvent(const SDL_Event& event) -> void;

    auto getRoom() -> Room& { return m_room; }
    auto getRoom() const -> const Room& { return m_room; }

    auto cycleFurnitureCatalogue() -> void { DEBUG::cycleFurnitureCatalogue(m_catalogue); }
    auto beginPlacement() -> void;
    auto updatePlacementPreview() -> void;
    auto confirmPlacement() -> void;
    auto cancelPlacement() -> void;

    private:
    Room& m_room;
    FurnitureCatalogue m_catalogue {};

    Texture m_woodFloorTileTexture;
    Texture m_northWallTileTexture;
    Texture m_eastWallTileTexture;
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
}
