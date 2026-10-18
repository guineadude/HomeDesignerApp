#pragma once

#include <SDL3/SDL.h>

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
    auto handleEvent(const SDL_Event& event) -> SDL_AppResult;
    auto iterate() -> SDL_AppResult;
    private:
    static constexpr int vsyncRefreshInterval {1};
    static constexpr int windowWidth {1280};
    static constexpr int windowHeight {720};

    SDL_Window*   m_window    {nullptr};
    SDL_Renderer* m_renderer  {nullptr};
    bool          m_isVideoInitialised {false};
    auto shutdown() -> void;
};