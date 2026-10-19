#include "RoomScene.hpp"

auto RoomScene::generateFloor() -> void
{
    const auto roomWidth { m_room.getWidth() };
    const auto roomDepth { m_room.getDepth() };
    for (int y = 0; y < roomDepth; ++y)
    {
        for (int x = 0; x < roomWidth; ++x)
        {
            // Initialize or modify the tile as needed
        } 
    }
}