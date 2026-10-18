#define SDL_MAIN_USE_CALLBACKS

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <string>

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{
    (void)argc;
    (void)argv;
    *appstate = nullptr;

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "SDL_Init failed: %s",
                     SDL_GetError());
        return SDL_APP_FAILURE;
    }

    const char* basePath = SDL_GetBasePath();
    if (basePath == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Could not get the application base path: %s",
                     SDL_GetError());
        SDL_Quit();
        return SDL_APP_FAILURE;
    }
    SDL_Log("Read-only asset base path: %s", basePath);

    char* prefPath = SDL_GetPrefPath("HomeDesignerApp", "HomeDesignerApp");
    if (prefPath == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Could not get the user data path: %s",
                     SDL_GetError());
        SDL_Quit();
        return SDL_APP_FAILURE;
    }

    const std::string userDataPath{prefPath};
    SDL_free(prefPath);
    SDL_Log("Writable user data path: %s", userDataPath.c_str());

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
    (void)appstate;
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    (void)appstate;
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    (void)appstate;
    (void)result;
    SDL_Quit();
}
