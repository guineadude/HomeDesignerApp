#pragma once

#include <map>
#include "UIWrapper.hpp"
#include "HitTest.hpp"
#include "Collision.hpp"

namespace UI
{
    using WrapperKey = std::pair<std::size_t, std::string>;
}

class UIManager
{
public:
    auto addWrapper(const std::string& name, std::size_t z, UIWrapper w) -> void 
        { m_wrappers.emplace(UI::WrapperKey{z, name}, std::move(w)); }
    auto renderWrappers(SDL_Renderer* renderer) const -> void;
    auto toggleWrapper(const std::string& name) -> void;

    [[nodiscard]] auto getWrapper(const std::string& name) const -> const UIWrapper*;
    [[nodiscard]] auto getWrapper(const std::string& name) -> UIWrapper*;

    auto handleHover(const SDL_MouseMotionEvent& e) -> void;
    auto handleMouseButton(const SDL_MouseButtonEvent& e) -> void;
    
    auto clear() -> void 
        { m_wrappers.clear(); }
private:

    std::map<UI::WrapperKey, UIWrapper> m_wrappers {};
};