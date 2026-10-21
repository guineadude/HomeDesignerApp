#pragma once

#include <SDL3/SDL.h>
#include <ranges>

#include "FurnitureCatalogue.hpp"
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
    auto handleEvent(const SDL_Event& event) -> void;

    auto getRoom() -> Room& { return m_room; }
    auto getRoom() const -> const Room& { return m_room; }

    //---------------------Furniture---------------------//
    auto cycleFurnitureCatalogue() -> void { m_catalogue.DEBUG_cycleFurnitureCatalogue(); }
    //---------------------Furniture---------------------//
    private:
    Room& m_room;
    FurnitureCatalogue m_catalogue {};

    //---------------------temporary floor tile textures---------------------//
    Texture m_woodFloorTileTexture;
    Texture m_northWallTileTexture;
    Texture m_eastWallTileTexture;
};