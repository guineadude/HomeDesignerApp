#include "graphics/TextureManager.hpp"

auto TextureManager::unload(std::string_view path) -> void
{
    m_textures.erase(path);
}

auto TextureManager::clear() -> void
{
    m_textures.clear();
}

auto TextureManager::get(std::string_view path) const -> const Texture*
{
    auto it { m_textures.find(path) };
    if(it != m_textures.end()) return &it->second;
    return nullptr;
}

auto TextureManager::load(SDL_Renderer* renderer, std::string_view path) -> bool
{
    if (m_textures.contains(path))
        return true;

    Texture texture{};
    const auto fullPath{std::string{m_basePath}.append(path)};

    if (!texture.load(renderer, fullPath))
        return false;

    m_textures.emplace(path, std::move(texture));
    return true;
}
