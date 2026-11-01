#pragma once

#include <SDL3/SDL.h>

#include <memory>
#include <string>

struct TextureDeleter
{
    void operator()(SDL_Texture* texture) const
    {
        SDL_DestroyTexture(texture);   
    }
};

class Texture
{
public:
    [[nodiscard]] auto load(SDL_Renderer* renderer, const std::string& filePath) -> bool;
    [[nodiscard]] auto get() const -> SDL_Texture* { return m_texture.get(); }
    auto width() const -> float
    {
        return m_texture
            ? static_cast<float>(m_texture->w)
            : 0.0f;
    }
    auto height() const -> float
    {
        return m_texture
            ? static_cast<float>(m_texture->h)
            : 0.0f;
    }
private:
    std::unique_ptr<SDL_Texture, TextureDeleter> m_texture;
};