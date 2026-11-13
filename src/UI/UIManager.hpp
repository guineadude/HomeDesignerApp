#pragma once

#include <unordered_map>
#include "UIWrapper.hpp"
#include "HitTest.hpp"
#include "Collision.hpp"

class UIManager
{
public:
    auto addWrapper(const std::string& name, UIWrapper w) -> void 
        { m_wrappers.emplace(name, std::move(w)); }
    auto renderWrappers(SDL_Renderer* renderer) const -> void;
    
    auto getWrapper(const std::string& name) const -> const UIWrapper*;
    auto getWrapper(const std::string& name) -> UIWrapper*;

    auto handleHover(const SDL_MouseMotionEvent& e) -> void;
    auto handleMouseButton(const SDL_MouseButtonEvent& e) -> void;
    auto clear() -> void { m_wrappers.clear(); }
private:
    std::unordered_map<std::string, UIWrapper> m_wrappers {};

};