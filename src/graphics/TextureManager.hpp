#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <SDL3/SDL.h>   
#include <stdexcept>
#include <utility>

#include "Texture.hpp"

class TextureManager
{
public:
    TextureManager() : m_basePath{ SDL_GetBasePath() } 
    {
        if(!m_basePath)
        {
            throw std::runtime_error("Failed to get base path");
        }
    }

    [[nodiscard]] auto load(SDL_Renderer* renderer, const std::string& path) -> bool;
    [[nodiscard]] auto get(std::string_view path) const -> const Texture*;
    auto clear() -> void;
    auto unload(std::string_view path) -> void;
    
private:
    std::unordered_map<std::string, Texture> m_textures;
    const char* m_basePath{};
};


