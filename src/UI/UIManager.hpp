#pragma once

#include <unordered_map>
#include "UIWrapper.hpp"

class UIManager
{
public:
    auto addWrapper(const std::string& name, UIWrapper w) -> void 
        { m_wrappers.emplace(name, std::move(w)); }
    auto renderWrappers(SDL_Renderer* renderer) const -> void;
    auto clear() -> void { m_wrappers.clear(); }
private:
    std::unordered_map<std::string, UIWrapper> m_wrappers {};

};