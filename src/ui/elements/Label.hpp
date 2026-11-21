#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cmath>
#include <optional>
#include <stdexcept>
#include <string>
#include "graphics/TextRenderer.hpp"

struct LabelConfig
{
    SDL_FPoint               position {};
    std::string              text {};
    float                    pointSize {16.0f};
    SDL_Color                color {255, 255, 255, 255};
    std::optional<SDL_FRect> centerIn {};   // if set, text is centered in this rect and position is ignored
};

class Label
{
public:
    Label(LabelConfig config, TextRenderer& textRenderer)
    : m_pos(config.position),
      m_text(textRenderer.createText(config.text, config.pointSize, config.color))
    {
        if(!m_text)
            throw std::runtime_error("Failed to create label text");

        const SDL_Point size{TextRenderer::size(m_text)};
        const auto width{static_cast<float>(size.x)};
        const auto height{static_cast<float>(size.y)};

        if(config.centerIn)
        {
            const SDL_FRect& box{*config.centerIn};
            m_pos = { std::floor(box.x + (box.w - width) / 2.0f),
                      std::floor(box.y + (box.h - height) / 2.0f) };
        }

        m_bounds = { m_pos.x, m_pos.y, width, height };
    }

    // renderer unused: a TTF_Text from the renderer text engine already knows where to draw
    auto render(SDL_Renderer*) const -> void
    {
        TTF_DrawRendererText(m_text.get(), m_pos.x, m_pos.y);
    }

    [[nodiscard]] auto getCollider() const -> SDL_FRect { return m_bounds; }

    auto onHover(bool) -> void {}
    auto onPress(bool) -> void {}
    auto onRelease(bool) -> void {}

private:
    SDL_FPoint m_pos {};
    SDL_FRect  m_bounds {};
    Text       m_text {};
};
