#pragma once

#include <SDL3/SDL.h>
#include <functional>
#include <array>
#include <optional>
#include <stdexcept>
#include <string>

#include "graphics/Texture.hpp"
#include "ui/elements/NineSlice.hpp"

enum class ScrollBarState
{
    Normal,
    Hovered,
    Pressed
};

struct ScrollBarConfig
{
    SDL_FRect thumbBounds {};
    SDL_FRect trackBounds {};
    std::function<void()> m_onScroll {};
    std::string thumbTexturePath {};
    std::string trackTexturePath {};
    struct ThumbSources
    {
        SDL_FRect normal {};
        SDL_FRect hovered {};
        SDL_FRect pressed {};
    } sources {};
    SDL_FRect trackSource {};
    std::optional<UI::NineSlice> nineSlice {};   // applied to both track and thumb
};

class ScrollBar
{
public:
    ScrollBar(ScrollBarConfig cfg, SDL_Renderer* renderer)
     : m_thumbBounds(cfg.thumbBounds)
     , m_trackBounds(cfg.trackBounds)
     , m_thumbSources { cfg.sources.normal, cfg.sources.hovered, cfg.sources.pressed } 
     , m_trackSource(cfg.trackSource)
     , m_scroll(cfg.m_onScroll)
     , m_nineSlice(cfg.nineSlice)
    {
        if(!m_scroll)
        throw std::runtime_error("No scroll handler");

    // loaded once; state changes only swap the source rect
    if(!m_thumbTexture.load(renderer, cfg.thumbTexturePath))
        throw std::runtime_error("Failed to load thumb texture");
    if(!m_trackTexture.load(renderer, cfg.trackTexturePath))
        throw std::runtime_error("Failed to load track texture");
    }

    auto render(SDL_Renderer* renderer) const -> void
    {
        renderPart(renderer, m_trackTexture, m_trackSource, m_trackBounds);
        renderPart(renderer, m_thumbTexture, sourceRectFor(m_state), m_thumbBounds);
    }

    [[nodiscard]] auto getThumbCollider() const -> SDL_FRect { return m_thumbBounds; }
    [[nodiscard]] auto getTrackCollider() const -> SDL_FRect { return m_trackBounds; }
    [[nodiscard]] auto getCollider() const -> SDL_FRect { return m_thumbBounds; }

    auto onHover(bool isHovered) -> void
    {
        // if(!isHovered)
        //     m_state = ScrollBarState::Normal;
        // else if(m_state != ScrollBarState::Pressed)
        //     m_state = ScrollBarState::Hovered;
    }

    auto onPress(bool isHit) -> void
    {
        // if(isHit)
        //     m_state = ScrollBarState::Pressed;
    }

    auto onRelease(bool isHit) -> void
    {
        // const bool wasPressed{m_state == ScrollBarState::Pressed};
        // m_state = isHit ? ScrollBarState::Hovered : ScrollBarState::Normal;
        // if(wasPressed && isHit)
        //     m_scroll();
    }

    auto onScroll(int delta) -> void 
    {
        m_scroll(); 
    }

    auto onMouseMove(float x, float y) -> void
    {

    }

private:
    Texture m_thumbTexture {};
    Texture m_trackTexture {};
    SDL_FRect m_thumbBounds {};
    SDL_FRect m_trackBounds {};
    std::array<SDL_FRect, 3> m_thumbSources {};   // indexed by ScrollBarState
    SDL_FRect m_trackSource {};
    std::function<void()> m_scroll {};
    ScrollBarState m_state { ScrollBarState::Normal };
    std::optional<UI::NineSlice> m_nineSlice {};

    auto renderPart(SDL_Renderer* renderer, const Texture& texture,
                    const SDL_FRect& source, const SDL_FRect& dest) const -> void
    {
        if(m_nineSlice)
            SDL_RenderTexture9Grid(renderer, texture.get(), &source,
                                   m_nineSlice->left, m_nineSlice->right, m_nineSlice->top, m_nineSlice->bottom,
                                   m_nineSlice->scale, &dest);
        else
            texture.render(renderer, &source, &dest);
    }

    [[nodiscard]] auto sourceRectFor(ScrollBarState state) const -> const SDL_FRect&
    { return m_thumbSources[static_cast<std::size_t>(state)]; }
};
