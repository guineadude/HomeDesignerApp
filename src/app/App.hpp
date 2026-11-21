#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "room/Room.hpp"
#include "scenes/RoomScene.hpp"
#include "graphics/TextRenderer.hpp"
#include "ui/UIManager.hpp"

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
    constexpr static int vsyncRefreshInterval {1};
    constexpr static int windowWidth {1280};
    constexpr static int windowHeight {720};
    constexpr static std::string_view fontPath {"assets/fonts/PixelifySans/PixelifySans.ttf"};

    SDL_Window*   m_window    {nullptr};
    SDL_Renderer* m_renderer  {nullptr};
    RoomBuildInstructions m_buildInstructions {};
    Room          m_room      {m_buildInstructions};
    RoomScene     m_roomScene {m_room, m_buildInstructions};
    UIManager     m_uiManager;
    TextRenderer  m_textRenderer {}; 

    bool          m_isVideoInitialised {false};
    bool          m_isTTFInitialised {false};
    
    auto shutdown() -> void;
};