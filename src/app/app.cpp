#include "app.hpp"

#include "SDL3/SDL_events.h"
#include "debug.hpp"

auto App::init() -> bool
{
    if(!SDL_Init(SDL_INIT_VIDEO))
    {
        Core::Debug::log("SDL_Init failed: ", SDL_GetError());
        return false;
    }

    m_isVideoInitialised = true;
    m_window = SDL_CreateWindow(
        "Home Designer Focus App",
        windowWidth,
        windowHeight,
        SDL_WINDOW_RESIZABLE
    );

    if(!m_window)
    {
        Core::Debug::log("SDL_CreateWindow failed: ", SDL_GetError());
        return false;
    }

    if(!TTF_Init())
    {
        Core::Debug::log("TTF_Init failed: ", SDL_GetError());
        return false;
    }
    m_isTTFInitialised = true;

    m_renderer = SDL_CreateRenderer(m_window, nullptr);
    if(!m_renderer)
    {
        Core::Debug::log("SDL_CreateRenderer failed: ", SDL_GetError());
        return false;
    }

    if(!SDL_SetRenderVSync(m_renderer, vsyncRefreshInterval))
    {
        Core::Debug::log("SDL_SetRenderVSync failed: ", SDL_GetError());
        return false;
    }

    if(!m_textRenderer.init(m_renderer, fontPath))
    {
        Core::Debug::log("Failed to initialise text renderer");
        return false;
    }

    if(!m_roomScene.loadTextures(m_renderer, m_textRenderer))
    {
        Core::Debug::log("Failed to load textures");
        return false;
    }

    try
    {
        UIWrapper mainWrapper {};
        mainWrapper.elements.emplace_back(std::in_place_type<Button>,
            ButtonConfig{
                .position    = SDL_FPoint{ .x = 16.0f, .y = 64.0f },
                // 4x the 24x14 sprite so pixels scale evenly.
                .bounds      = SDL_FRect{ .x = 16.0f, .y = 64.0f, .w = 96.0f, .h = 56.0f },
                // Blank beige button, top row of Modern_UI_Style_1.png.
                .sourceRect  = SDL_FRect{ .x = 460.0f, .y = 1.0f, .w = 24.0f, .h = 14.0f },
                .onClick     = [] { Core::Debug::log("Button clicked"); },
                .texturePath = std::string{buttonTexturePath},
            },
            m_renderer);

        m_uiManager.addWrapper("main", std::move(mainWrapper));
    }
    catch (const std::exception& e)
    {
        Core::Debug::log("Failed to create button: ", e.what());
        return false;
    }
    

    return true;
}

auto App::handleEvent(const SDL_Event& event) -> SDL_AppResult
{
    //handle app events
    if(event.type == SDL_EVENT_QUIT
        || (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE))
        return SDL_APP_SUCCESS;

    //if click, try handle UI
    if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
        m_uiManager.handleClick(SDL_MouseButtonEvent{event.button});
    //handle room scene events
    m_roomScene.handleEvent(event);

    return SDL_APP_CONTINUE;
}

auto App::update() -> SDL_AppResult
{
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);

    m_roomScene.update();
    m_roomScene.render(m_renderer);
    m_roomScene.renderUI(m_renderer, m_uiManager);
    
    SDL_RenderPresent(m_renderer);

    return SDL_APP_CONTINUE;
}

auto App::shutdown() -> void
{
    m_roomScene.shutdown();
    m_textRenderer.shutdown();
    if(m_renderer)
    {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
    if(m_window)
    {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
    if(m_isTTFInitialised)
    {
        TTF_Quit();
        m_isTTFInitialised = false;
    }
    if(m_isVideoInitialised)
    {
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        m_isVideoInitialised = false;
    }
}