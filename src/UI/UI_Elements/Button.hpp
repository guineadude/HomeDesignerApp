#pragma once

#include <SDL3/SDL.h>
#include <functional>
#include "Texture.hpp"
#include <string>
#include <stdexcept>

enum class ButtonState
{
    Normal,
    Hovered,
    Pressed,
};

class Button 
{
public:
    Button(SDL_FPoint pos,
           SDL_FRect bounds,
           std::function<void()> onClick,
           const std::string& text,
           SDL_Renderer* renderer)
        : m_bounds(bounds), m_pos(pos) 
    {
        click = std::move(onClick);
        if(!click)
            throw std::runtime_error("No click handler");

        if(!m_texture.load(renderer, text))
            throw std::runtime_error("Failed to load texture");
    }

    [[nodiscard]] auto load(SDL_Renderer* renderer) -> bool
    {
        return true;
    }

    auto render(SDL_Renderer* renderer) const -> void
    {

    }

    auto onClick() -> void { click(); }
private:
    ButtonState m_state { ButtonState::Normal };
    SDL_FRect m_bounds {};
    SDL_FPoint m_pos {};
    std::function<void()> click {};
    Texture m_texture;
};

