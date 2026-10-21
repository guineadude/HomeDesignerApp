#pragma once

#include <SDL3/SDL.h>

#include "FurnitureCatalogue.hpp"
#include "Room.hpp"
#include "Texture.hpp"

class RoomScene
{
    public:
    RoomScene(Room& room)
        : m_room(room)
    {}
    //---------------------Core Functions---------------------//
    auto loadTextures(SDL_Renderer* renderer) -> void;
    auto render(SDL_Renderer* renderer) -> void;
    auto handleEvent(const SDL_Event& event) -> void;
    //---------------------Core Functions---------------------//

    //---------------------Getters---------------------//
    auto getRoom() -> Room& { return m_room; }
    auto getRoom() const -> const Room& { return m_room; }
    //---------------------Getters---------------------//

    //---------------------Furniture/Placement---------------------//
    auto cycleFurnitureCatalogue() -> void { m_catalogue.DEBUG_cycleFurnitureCatalogue(); }
    auto beginPlacement() -> void;
    auto updatePlacementPreview() -> void;
    auto confirmPlacement() -> void;
    auto cancelPlacement() -> void;
    //---------------------Furniture/Placement---------------------//
    private:
    Room& m_room;
    FurnitureCatalogue m_catalogue {};

    //---------------------temporary floor tile textures---------------------//
    Texture m_woodFloorTileTexture;
    Texture m_northWallTileTexture;
    Texture m_eastWallTileTexture;
};