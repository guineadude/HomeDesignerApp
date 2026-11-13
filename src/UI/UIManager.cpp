#include "UIManager.hpp"
#include "HitTest.hpp"

auto UIManager::renderWrappers(SDL_Renderer* renderer) const -> void
{
    const auto renderElement = [&](const auto& el)
    {
        std::visit([&](const auto& element)
        {
            element.render(renderer);
        }, el);
    };

    for (const auto& [name, wrapper] : m_wrappers)
    {
        for (const auto& el : wrapper.elements)
        {
            renderElement(el);
        }
    }
}

auto UIManager::handleMouseButton(const SDL_MouseButtonEvent& e) -> void
{
    const SDL_FPoint mousePos{e.x, e.y};
    const bool isDown{e.type == SDL_EVENT_MOUSE_BUTTON_DOWN};

    for (auto& [name, wrapper] : m_wrappers)
        for (auto& el : wrapper.elements)
            std::visit([&](auto& element)
            {
                const bool hit{Collision::checkMouseHit(mousePos, element.getCollider())};
                if(isDown)
                    element.onPress(hit);
                else
                    element.onRelease(hit);
            }, el);
}


auto UIManager::handleHover(const SDL_MouseMotionEvent& e) -> void
{
    if(e.type != SDL_EVENT_MOUSE_MOTION) return;
    const auto mousePos { HitTest::handleMouseMotion(e) };
    const auto updateHover = [&mousePos](auto& el)
    {
        std::visit([&](auto& element)
        {
            element.onHover(Collision::checkMouseHit(mousePos, element.getCollider()));
        }, el);
    };

    for (auto& [name, wrapper] : m_wrappers)
    {
        for (auto& el : wrapper.elements)
            updateHover(el);
    }
}

auto UIManager::getWrapper(const std::string& name) const -> const UIWrapper*
{
    auto it { m_wrappers.find(name) };
    return it != m_wrappers.end() ? &it->second : nullptr;
}
auto UIManager::getWrapper(const std::string& name) -> UIWrapper*
{
    auto it { m_wrappers.find(name) };
    return it != m_wrappers.end() ? &it->second : nullptr;
}