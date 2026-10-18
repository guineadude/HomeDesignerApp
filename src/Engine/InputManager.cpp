// SDL event handling for the unified mouse/touch pointer state.
#include "Engine/InputManager.h"

namespace HomeDesigner::Engine {

bool InputManager::handleEvent(const SDL_Event& event) noexcept
{
    switch (event.type) {
    case SDL_EVENT_MOUSE_MOTION:
        m_pointer.x = event.motion.x;
        m_pointer.y = event.motion.y;
        m_pointer.source = PointerSource::Mouse;
        return true;

    case SDL_EVENT_MOUSE_BUTTON_DOWN:
    case SDL_EVENT_MOUSE_BUTTON_UP:
        m_pointer.x = event.button.x;
        m_pointer.y = event.button.y;
        m_pointer.isDown = event.type == SDL_EVENT_MOUSE_BUTTON_DOWN;
        m_pointer.source = PointerSource::Mouse;
        return true;

    case SDL_EVENT_FINGER_DOWN:
    case SDL_EVENT_FINGER_MOTION:
    case SDL_EVENT_FINGER_UP:
        m_pointer.x = event.tfinger.x;
        m_pointer.y = event.tfinger.y;
        m_pointer.isDown = event.type != SDL_EVENT_FINGER_UP;
        m_pointer.source = PointerSource::Touch;
        return true;

    default:
        return false;
    }
}

const PointerState& InputManager::pointer() const noexcept
{
    return m_pointer;
}

} // namespace HomeDesigner::Engine
