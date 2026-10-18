#include "app.hpp"

auto App::init() -> bool
{
    if(!SDL_Init(SDL_INIT_VIDEO))
        return false;

    if(!(m_window = SDL_CreateWindow(
        "Home Designer Focus App",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOW_RESIZABLE)))
        return false;

    if(!(m_renderer = SDL_CreateRenderer(m_window, nullptr)))
        return false;

    if(!SDL_SetRenderVSync(m_renderer, vsyncRefreshInterval))
        return false;

    return true;
}

auto App::run() -> int
{
    m_isRunning = true;
    while(m_isRunning)
    {
        SDL_Event event {};
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_EVENT_QUIT)
                m_isRunning = false;
        }

        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
        SDL_RenderClear(m_renderer);
        SDL_RenderPresent(m_renderer);
    }

    return 0;
}

auto App::shutdown() -> void
{
    if(m_window)
        SDL_DestroyWindow(m_window);
    if(m_renderer)
        SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
}