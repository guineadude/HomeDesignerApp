#pragma once

#include <string_view>
#include <unordered_map>
#include <SDL3/SDL.h>   

#include "Texture.hpp"

class TextureManager
{
public:
    [[nodiscard]] auto load(SDL_Renderer* renderer, std::string_view path) -> bool;
    [[nodiscard]] auto get(std::string_view path) -> Texture&;
    auto clear() -> void;
private:
    std::unordered_map<std::string_view, Texture> m_textures;
};
