#pragma once

#include <SDL3/SDL.h>
#include "graphics/Texture.hpp"
#include <string>
#include <functional>
#include <stdexcept>
#include <optional>
#include "ui/elements/NineSlice.hpp"

struct WindowConfig
{
    SDL_FPoint            position {};
    SDL_FRect             bounds {};
    SDL_FRect             sourceRect {};
    std::string           texturePath {};
    std::function<void()> onClick {};
    std::optional<UI::NineSlice> nineSlice {};
};


class Window
{
public:
    Window(WindowConfig cfg, SDL_Renderer* renderer)
    : m_bounds(cfg.bounds),
    m_sourceRect(cfg.sourceRect),
    m_pos(cfg.position),
    click(std::move(cfg.onClick)),
    m_nineSlice(cfg.nineSlice)
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
        if(m_nineSlice)
            SDL_RenderTexture9Grid(renderer, m_texture.get(), &m_sourceRect,
                                m_nineSlice->left, m_nineSlice->right, m_nineSlice->top, m_nineSlice->bottom,
                                m_nineSlice->scale,
                                &m_bounds);
        if(!m_nineSlice)
            m_texture.render(renderer, &m_sourceRect, &m_bounds);
    }

    [[nodiscard]] auto getCollider() const -> SDL_FRect { return m_bounds; }

    auto onHover(bool) -> void {}
    auto onPress(bool) -> void {}
    auto onRelease(bool isHit) -> void
    {
        if(isHit)
            click();
    }

private:
    SDL_FRect m_bounds {};
    SDL_FRect m_sourceRect {};
    SDL_FPoint m_pos {};
    std::function<void()> click {};
    Texture m_texture;
    std::optional<UI::NineSlice> m_nineSlice;
};
