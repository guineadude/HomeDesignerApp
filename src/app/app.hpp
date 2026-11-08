#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Room.hpp"
#include "RoomScene.hpp"
#include "TextRenderer.hpp"
#include "UIManager.hpp"

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
    auto update() -> SDL_AppResult;
    
private:
    static constexpr int vsyncRefreshInterval {1};
    static constexpr int windowWidth {1280};
    static constexpr int windowHeight {720};
    static constexpr std::string_view fontPath {"assets/fonts/PixelifySans/PixelifySans.ttf"};

    SDL_Window*   m_window    {nullptr};
    SDL_Renderer* m_renderer  {nullptr};
    RoomBuildInstructions m_buildInstructions {};
    Room          m_room      {m_buildInstructions};
    RoomScene     m_roomScene {m_room, m_buildInstructions};
    UIManager     m_uiManager {};
    TextRenderer  m_textRenderer {}; 

    bool          m_isVideoInitialised {false};
    bool          m_isTTFInitialised {false};
    
    auto shutdown() -> void;
};