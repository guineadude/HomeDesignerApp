#pragma once

#include <SDL3/SDL.h>

namespace
{
    constexpr static int vsyncRefreshInterval {1};
}

class App
{
    public:
    App() = default;
    ~App() { shutdown(); };
    App(const App&) = delete;
    App& operator=(const App&) = delete;
    App(App&&) = delete;
    App& operator=(App&&) = delete;

    auto init() -> bool;
    auto run() -> int;
    private:
    SDL_Window*   m_window   {nullptr};
    SDL_Renderer* m_renderer {nullptr};

    auto shutdown() -> void;
};