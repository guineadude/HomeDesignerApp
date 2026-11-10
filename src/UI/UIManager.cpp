#include "UIManager.hpp"

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