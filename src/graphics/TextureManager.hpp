#pragma once

#include <string>
#include <unordered_map>
#include <SDL3/SDL.h>   

#include "Texture.hpp"

class TextureManager
{
public:
    TextureManager() 
    {
        
    }

    [[nodiscard]] auto load(SDL_Renderer* renderer, std::string path) -> bool;
    [[nodiscard]] auto get(std::string path) -> const Texture*;
    auto clear() -> void;
private:
    std::unordered_map<std::string, Texture> m_textures;
    const char* m_basePath{SDL_GetBasePath()};
};


