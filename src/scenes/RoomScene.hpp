#pragma once

#include "Room.hpp"

class RoomScene
{
    public:
    RoomScene(Room& room)
        : m_room(room)
    {}

    auto getRoom() -> Room& { return m_room; }
    auto getRoom() const -> const Room& { return m_room; }

    private:
    Room& m_room;
};