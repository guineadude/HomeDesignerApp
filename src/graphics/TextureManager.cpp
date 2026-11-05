#include "TextureManager.hpp"

auto TextureManager::unload(std::string_view path) -> void
{
    m_textures.erase(std::string{path});
}

auto TextureManager::clear() -> void
{
    m_textures.clear();
}

auto TextureManager::get(std::string_view path) const -> const Texture*
{
    auto it { m_textures.find(std::string{path}) };
    if(it != m_textures.end()) return &it->second;
    return nullptr;
}

auto TextureManager::load(SDL_Renderer* renderer, const std::string& path) -> bool
{
    if (m_textures.contains(path))
        return true;

    Texture texture{};

    if (!texture.load(renderer, std::string{m_basePath} + path))
        return false;

    m_textures.emplace(path, std::move(texture));
    return true;
}
