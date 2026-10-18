// SDL mouse and touch input state shared by the application engine.
#pragma once

#include <SDL3/SDL_events.h>

namespace HomeDesigner::Engine {

enum class PointerSource {
    None,
    Mouse,
    Touch
};

struct PointerState {
    float x{0.0F};
    float y{0.0F};
    bool isDown{false};
    PointerSource source{PointerSource::None};
};

class InputManager {
public:
    // Touch coordinates are normalized (0..1); mouse coordinates use window
    // coordinates.
    [[nodiscard]] bool handleEvent(const SDL_Event& event) noexcept;
    [[nodiscard]] const PointerState& pointer() const noexcept;

private:
    PointerState m_pointer{};
};

} // namespace HomeDesigner::Engine
