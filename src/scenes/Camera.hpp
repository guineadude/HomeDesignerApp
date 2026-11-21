#pragma once

#include <SDL3/SDL.h>
#include <algorithm>
#include <cmath>

class Camera
{
public:
    Camera() = default;
    ~Camera() = default;

    // camera functions
    auto move(SDL_FPoint delta) -> void
    {
        setCenter({m_center.x + delta.x, m_center.y + delta.y});
    }
    auto zoomIn() -> void
    {
        m_zoom = std::min(m_zoom + k_zoomFactor, k_maxZoom);
    }
    auto zoomOut() -> void
    {
        m_zoom = std::max(m_zoom - k_zoomFactor, k_minZoom);    
    }

    // setters
    auto setCenter(SDL_FPoint center) -> void { m_center = center; }

    // getters for camera info
    [[nodiscard]] auto getCenter() const -> SDL_FPoint { return m_center; }
    [[nodiscard]] auto getZoomFactor() const -> int { return m_zoom; }

    // convert points between world and screen
    public:
    [[nodiscard]] auto worldToScreen(SDL_FPoint world, SDL_FPoint screenSize) const noexcept -> SDL_FPoint
    {
        const SDL_FPoint topLeft {viewTopLeft(screenSize)};
        const auto zoom {static_cast<float>(m_zoom)};
        return { (world.x - topLeft.x) * zoom,
                 (world.y - topLeft.y) * zoom };
    }
    [[nodiscard]] auto screenToWorld(SDL_FPoint screen, SDL_FPoint screenSize) const noexcept -> SDL_FPoint
    {
        const SDL_FPoint topLeft {viewTopLeft(screenSize)};
        const auto zoom {static_cast<float>(m_zoom)};
        return { screen.x / zoom + topLeft.x,
                 screen.y / zoom + topLeft.y };
    }
    [[nodiscard]] auto rectToScreen(const SDL_FRect& world, SDL_FPoint screenSize) const noexcept -> SDL_FRect
    {
        const SDL_FPoint pos {worldToScreen({world.x, world.y}, screenSize)};
        const auto zoom {static_cast<float>(m_zoom)};
        return { pos.x, pos.y, world.w * zoom, world.h * zoom };
    }

private:
    [[nodiscard]] auto viewTopLeft(SDL_FPoint screenSize) const noexcept -> SDL_FPoint
    {
        const auto zoom {static_cast<float>(m_zoom)};
        return { std::floor(m_center.x - screenSize.x / (2.f * zoom)),
                 std::floor(m_center.y - screenSize.y / (2.f * zoom)) };
    }

private:
    constexpr static int k_zoomFactor {1};
    constexpr static int k_minZoom {1};
    constexpr static int k_maxZoom {4};
    int m_zoom {1};
    SDL_FPoint m_center {};

};