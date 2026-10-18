// Basic storage operations for the SDL-independent layout model.
#include "Core/LayoutModel.h"

#include <utility>

namespace HomeDesigner::Core {

void LayoutModel::addRoom(Room room)
{
    m_rooms.push_back(std::move(room));
}

void LayoutModel::clear() noexcept
{
    m_rooms.clear();
}

const std::vector<Room>& LayoutModel::rooms() const noexcept
{
    return m_rooms;
}

} // namespace HomeDesigner::Core
