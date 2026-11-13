#pragma once

#include <SDL3/SDL.h>
#include <functional>
#include "Texture.hpp"
#include <string>
#include <utility>
#include <stdexcept>
#include <array>
#include <cstddef>

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
    std::function<void()> onClick {};
    std::string           texturePath {};   // one sheet holding every state
    struct Sources
    {
        SDL_FRect normal {};
        SDL_FRect hovered {};
        SDL_FRect pressed {};
    } sources {};
};

class Button
{
public:
    Button(ButtonConfig config, SDL_Renderer* renderer)
    : m_sources{ config.sources.normal, config.sources.hovered, config.sources.pressed },
      m_click(std::move(config.onClick)),
      m_bounds(config.bounds)
    {
        if(!m_click)
            throw std::runtime_error("No click handler");

        // loaded once; state changes only swap the source rect
        if(!m_texture.load(renderer, config.texturePath))
            throw std::runtime_error("Failed to load texture");
    }

    auto render(SDL_Renderer* renderer) const -> void
    {
        m_texture.render(renderer, &sourceRectFor(m_state), &m_bounds);
    }

    auto onHover(bool isHovered) -> void
    {
        if(!isHovered)
            m_state = ButtonState::Normal;
        else if(m_state != ButtonState::Pressed)
            m_state = ButtonState::Hovered;
    }

    auto onPress(bool isHit) -> void
    {
        if(isHit)
            m_state = ButtonState::Pressed;
    }

    auto onRelease(bool isHit) -> void
    {
        const bool wasPressed{m_state == ButtonState::Pressed};
        m_state = isHit ? ButtonState::Hovered : ButtonState::Normal;
        if(wasPressed && isHit)
            m_click();
    }

    [[nodiscard]] auto getCollider() const -> SDL_FRect { return m_bounds; }

private:
    Texture m_texture {};
    std::array<SDL_FRect, 3> m_sources {};   // indexed by ButtonState
    std::function<void()> m_click {};
    SDL_FRect m_bounds {};
    ButtonState m_state { ButtonState::Normal };

    [[nodiscard]] auto sourceRectFor(ButtonState state) const -> const SDL_FRect&
        { return m_sources[static_cast<std::size_t>(state)]; }
};
