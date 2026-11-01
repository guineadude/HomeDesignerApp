#include "Texture.hpp"

#include <cassert>
#include "debug.hpp"
#include <SDL3_image/SDL_image.h>

auto Texture::load(SDL_Renderer* renderer, const std::string& filePath) -> bool
{   
    assert(renderer != nullptr &&
        "Texture::load requires a valid renderer");

    SDL_Surface* surface { IMG_Load(filePath.c_str()) };

    if (!surface)
    {
        Core::Debug::log("Failed to load image '", filePath, "': ", SDL_GetError());
        return false;
    }
    
    auto* newTexture { SDL_CreateTextureFromSurface(renderer, surface) };
    SDL_DestroySurface(surface);
    
    if (!newTexture)
    {
        Core::Debug::log("Failed to create texture from '", filePath, "': ", SDL_GetError());
        return false;
    }

    m_texture.reset(newTexture);
    return true;
}