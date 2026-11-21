#define SDL_MAIN_USE_CALLBACKS

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <memory>

#include "app/App.hpp"

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    (void)argc;
    (void)argv;
    *appstate = nullptr;

    auto app = std::make_unique<App>();
    if (!app->init())
        return SDL_APP_FAILURE;

    *appstate = app.release();
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
    return static_cast<App*>(appstate)->update();
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    return static_cast<App*>(appstate)->handleEvent(*event);
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    (void)result;
    delete static_cast<App*>(appstate);
}
