#include "Texture.hpp"

auto Texture::load(SDL_Renderer* renderer, const std::string& filePath) -> bool
{
    SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
    if (!surface)
    {
        SDL_Log("Failed to load BMP file: %s", SDL_GetError());
        return false;
    }

    m_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!m_texture)
    {
        SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
        return false;
    }

    return true;
}