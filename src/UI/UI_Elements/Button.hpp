#pragma once

#include <SDL3/SDL.h>
#include <functional>
#include "Texture.hpp"
#include <string>
#include <utility>
#include <stdexcept>
#include <utility>
#include <array>

namespace UI {
    using ElementTexSource = std::pair<std::string, SDL_FRect>;
    using ElementTex = std::pair<Texture, SDL_FRect>;
} 


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
    struct Textures
    {
        UI::ElementTexSource normal {};
        UI::ElementTexSource hovered {};
        UI::ElementTexSource pressed {};
    } textures {};
};

class Button
{
public:
    Button(ButtonConfig config, SDL_Renderer* renderer)
    : m_bounds(config.bounds),
      click(std::move(config.onClick))
    {
        if(!click)
        {
            throw std::runtime_error("No click handler");
        }
        
        auto emplaceTex = [&](int i, const std::string& path, const SDL_FRect& rect)
        {
            Texture tex {};
            if(!tex.load(renderer, path))
                throw std::runtime_error("Failed to load texture");
            m_texture[i].first = std::move(tex);
            m_texture[i].second = rect;
        };

        emplaceTex(0, config.textures.normal.first, config.textures.normal.second);
        emplaceTex(1, config.textures.hovered.first, config.textures.hovered.second);
        emplaceTex(2, config.textures.pressed.first, config.textures.pressed.second);
    
    }

    auto render(SDL_Renderer* renderer) const -> void
    {
        textureFor(m_state).render(renderer, &sourceRectFor(m_state), &m_bounds);
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
            click();
    }
    
    [[nodiscard]] auto getCollider() const -> SDL_FRect { return m_bounds; }

private:
    std::array<UI::ElementTex, 3> m_texture {};
    std::function<void()> click {};
    SDL_FRect m_bounds {};
    ButtonState m_state { ButtonState::Normal };

    // get texture for state and source rect
    [[nodiscard]] auto textureFor(ButtonState state) -> Texture& { return m_texture[static_cast<std::size_t>(state)].first; }
    [[nodiscard]] auto textureFor(ButtonState state) const -> const Texture& { return m_texture[static_cast<std::size_t>(state)].first; }
    [[nodiscard]] auto sourceRectFor(ButtonState state) -> SDL_FRect& { return m_texture[static_cast<std::size_t>(state)].second; }
    [[nodiscard]] auto sourceRectFor(ButtonState state) const -> const SDL_FRect& { return m_texture[static_cast<std::size_t>(state)].second; }
};


    