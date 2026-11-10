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

auto UIManager::handleClick(const SDL_MouseButtonEvent& e) -> void
{
    if (e.type != SDL_EVENT_MOUSE_BUTTON_DOWN) return;
    const auto mousePos { HitTest::handleMouseButtonDown(e) };
    const auto doesCollide = [&mousePos](const auto& el)
    {
        std::visit([&](const auto& element)
        {
            if (Collision::checkMouseHit(mousePos, element.getCollider()))
                element.onClick();
        }, el);
    };

    for (const auto& [name, wrapper] : m_wrappers)
    {
        for (const auto& el : wrapper.elements)
            doesCollide(el);
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