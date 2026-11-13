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
    SDL_SetTextureScaleMode(m_texture.get(), SDL_SCALEMODE_NEAREST);
    return true;
}

auto Texture::render(SDL_Renderer* renderer, const SDL_FRect* destination) const -> void
{
    render(renderer, nullptr, destination);
}

auto Texture::render(SDL_Renderer* renderer, const SDL_FRect* source, const SDL_FRect* destination) const -> void
{
    if (!m_texture)
        return;

    SDL_RenderTexture(renderer, m_texture.get(), source, destination);
}