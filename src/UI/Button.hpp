#pragma once

#include <SDL3/SDL.h>
#include <functional>
#include "Texture.hpp"
#include <string_view>
#include <string>
enum class ButtonState
{
    Normal,
    Hovered,
    Pressed,
};

class Button 
{
public:
    Button(SDL_FRect bounds,
           std::function<void()> onClick,
           std::string_view text,
           SDL_Renderer* renderer)
        : m_bounds(bounds), click(std::move(onClick)) 
    {
        // const std::string basePath { SDL_GetBasePath() + text.cstr() };
        // m_texture.load(basePath, renderer);
    }
private:
    ButtonState m_state { ButtonState::Normal };
    SDL_FRect m_bounds {};
    std::function<void()> click {};
    Texture m_texture;
};