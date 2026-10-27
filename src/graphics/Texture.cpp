#include "Texture.hpp"

#include "debug.hpp"
#include <SDL3_image/SDL_image.h>

auto Texture::load(SDL_Renderer* renderer, const std::string& filePath) -> bool
{
    SDL_Surface* surface { IMG_Load(filePath.c_str()) };
    if (!surface)
    {
        Core::Debug::log("Failed to load image '", filePath, "': ", SDL_GetError());
        return false;
    }

    m_texture.reset(SDL_CreateTextureFromSurface(renderer, surface));
    SDL_DestroySurface(surface);
    if (!m_texture)
    {
        Core::Debug::log("Failed to create texture from '", filePath, "': ", SDL_GetError());
        return false;
    }

    return true;
}