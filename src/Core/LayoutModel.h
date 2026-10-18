// SDL-independent data model for rooms and their boundary walls.
#pragma once

#include <string>
#include <vector>

namespace HomeDesigner::Core {

struct Point2D {
    double x{0.0};
    double y{0.0};
};

struct Wall {
    Point2D start{};
    Point2D end{};
};

struct Room {
    std::string name;
    std::vector<Wall> walls;
};

class LayoutModel {
public:
    void addRoom(Room room);
    void clear() noexcept;

    [[nodiscard]] const std::vector<Room>& rooms() const noexcept;

private:
    std::vector<Room> m_rooms;
};

} // namespace HomeDesigner::Core
