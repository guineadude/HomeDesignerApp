#pragma once

#include <SDL3/SDL.h>
#include "Texture.hpp"
#include <string>
#include <functional>
#include <stdexcept>

struct WindowConfig
{
    SDL_FPoint            position {};
    SDL_FRect             bounds {};
    SDL_FRect             sourceRect {};
    std::string           texturePath {};
    std::function<void()> onClick {};
};


class Window
{
public:
    Window(WindowConfig cfg, SDL_Renderer* renderer)
    : m_bounds(cfg.bounds),
    m_sourceRect(cfg.sourceRect),
    m_pos(cfg.position),
    click(std::move(cfg.onClick))
    {
        if(!click)
            throw std::runtime_error("No click handler");
        if(!load(renderer, cfg.texturePath))
            throw std::runtime_error("Failed to load texture");
            
    }

    [[nodiscard]] auto load(SDL_Renderer* renderer, const std::string& texturePath) -> bool
    {
        if(!m_texture.load(renderer, texturePath))
            return false;

        SDL_SetTextureScaleMode(m_texture.get(), SDL_SCALEMODE_NEAREST);
        return true;
    }

    auto render(SDL_Renderer* renderer) const -> void
    {
        m_texture.render(renderer, &m_sourceRect, &m_bounds);
    }

    [[nodiscard]] auto getCollider() const -> SDL_FRect { return m_bounds; }

    auto onClick() const -> void { click(); }

private:
    SDL_FRect m_bounds {};
    SDL_FRect m_sourceRect {};
    SDL_FPoint m_pos {};
    std::function<void()> click {};
    Texture m_texture;
;
};
