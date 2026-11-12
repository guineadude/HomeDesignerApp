#pragma once

#include <SDL3/SDL.h>
#include <functional>
#include "Texture.hpp"
#include <string>
#include <stdexcept>
#include <utility>

enum class ButtonState
{
    Normal,
    Hovered,
    Pressed,
};

struct ButtonConfig
{
    SDL_FPoint            position {};
    SDL_FRect             bounds {};
    SDL_FRect             sourceRect {};   
    std::function<void()> onClick {};
    std::string           texturePath {};
};

class Button
{
public:
    Button(ButtonConfig config, SDL_Renderer* renderer)
    : m_bounds(config.bounds),
      m_sourceRect(config.sourceRect),
      m_pos(config.position),
      click(std::move(config.onClick))
    {
        if(!click)
            throw std::runtime_error("No click handler");

        if(!load(renderer, config.texturePath))
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
    ButtonState m_state { ButtonState::Normal };
    SDL_FRect m_bounds {};
    SDL_FRect m_sourceRect {};
    SDL_FPoint m_pos {};
    std::function<void()> click {};
    Texture m_texture;
};
