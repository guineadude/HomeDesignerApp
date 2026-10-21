#pragma once

#include <SDL3/SDL.h>
#include <ranges>

#include "Room.hpp"
#include "Texture.hpp"
#include "Isometric.hpp"

class RoomScene
{
    public:
    RoomScene(Room& room)
        : m_room(room)
    {}

    auto loadTextures(SDL_Renderer* renderer) -> void;
    auto render(SDL_Renderer* renderer) -> void;
    auto getRoom() -> Room& { return m_room; }
    auto getRoom() const -> const Room& { return m_room; }

    private:
    Room& m_room;

    //---------------------temporary floor tile textures---------------------//
    Texture m_woodFloorTileTexture;
    Texture m_northWallTileTexture;
    Texture m_eastWallTileTexture;
};