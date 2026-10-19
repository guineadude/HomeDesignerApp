#include "Texture.hpp"

#include <SDL3_image/SDL_image.h>

auto Texture::load(SDL_Renderer* renderer, const std::string& filePath) -> bool
{
    SDL_Surface* surface { IMG_Load(filePath.c_str()) };
    if (!surface)
    {
        SDL_Log("Failed to load image '%s': %s", filePath.c_str(), SDL_GetError());
        return false;
    }

    m_texture.reset(SDL_CreateTextureFromSurface(renderer, surface));
    SDL_DestroySurface(surface);
    if (!m_texture)
    {
        SDL_Log("Failed to create texture from '%s': %s", filePath.c_str(), SDL_GetError());
        return false;
    }

    return true;
}