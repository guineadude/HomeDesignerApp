#include "app.hpp"

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
        SDL_WINDOW_RESIZABLE);
    if(!m_window)
    {
        Core::Debug::log("SDL_CreateWindow failed: ", SDL_GetError());
        return false;
    }

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

    if(!m_roomScene.loadTextures(m_renderer))
    {
        Core::Debug::log("Failed to load textures");
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
    
    SDL_RenderPresent(m_renderer);

    return SDL_APP_CONTINUE;
}

auto App::shutdown() -> void
{
    m_roomScene.shutdown();
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
    if(m_isVideoInitialised)
    {
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        m_isVideoInitialised = false;
    }
}