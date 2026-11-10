#pragma once

#include <functional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <SDL3/SDL.h>   
#include <stdexcept>
#include <utility>
#include "Texture.hpp"

struct stringHash
{
    using is_transparent = void;
    auto operator()(std::string_view s) const noexcept -> std::size_t
    {
        return std::hash<std::string_view>{}(s);
    }
};

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

    [[nodiscard]] auto load(SDL_Renderer* renderer, std::string_view path) -> bool;
    [[nodiscard]] auto get(std::string_view path) const -> const Texture*;
    auto clear() -> void;
    auto unload(std::string_view path) -> void;
    
private:
    std::unordered_map<std::string, Texture, stringHash, std::equal_to<>> m_textures;
    const char* m_basePath{};
};


