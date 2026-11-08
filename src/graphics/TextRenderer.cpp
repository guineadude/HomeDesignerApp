#include "TextRenderer.hpp"

#include <cassert>

#include "debug.hpp"

auto TextRenderer::init(SDL_Renderer* renderer, std::string_view fontPath) -> bool
{
    assert(renderer != nullptr &&
        "TextRenderer::init requires a valid renderer");

    const char* basePath{ SDL_GetBasePath() };
    if (!basePath)
    {
        Core::Debug::log("SDL_GetBasePath failed: ", SDL_GetError());
        return false;
    }
    m_fontPath = std::string{basePath} + std::string{fontPath};

    m_engine.reset(TTF_CreateRendererTextEngine(renderer));
    if (!m_engine)
    {
        Core::Debug::log("TTF_CreateRendererTextEngine failed: ", SDL_GetError());
        return false;
    }

    return true;
}

auto TextRenderer::shutdown() -> void
{
    m_engine.reset();
    m_fonts.clear();
}

auto TextRenderer::font(float pointSize) -> TTF_Font*
{
    if (const auto it{ m_fonts.find(pointSize) }; it != m_fonts.end())
        return it->second.get();

    TTF_Font* opened{ TTF_OpenFont(m_fontPath.c_str(), pointSize) };
    if (!opened)
    {
        Core::Debug::log("Failed to open font '", m_fontPath, "' at ", pointSize, "pt: ", SDL_GetError());
        return nullptr;
    }

    TTF_SetFontHinting(opened, TTF_HINTING_MONO);

    m_fonts.emplace(pointSize, opened);
    return opened;
}

auto TextRenderer::createText(std::string_view string, float pointSize, SDL_Color color) -> Text
{
    assert(m_engine && "TextRenderer::createText called before init()");

    TTF_Font* sizedFont{ font(pointSize) };
    if (!sizedFont)
        return Text{};

    Text text{ TTF_CreateText(m_engine.get(), sizedFont, string.data(), string.size()) };
    if (!text)
    {
        Core::Debug::log("TTF_CreateText failed for '", string, "': ", SDL_GetError());
        return Text{};
    }

    TTF_SetTextColor(text.get(), color.r, color.g, color.b, color.a);
    return text;
}

auto TextRenderer::draw(const Text& text, float x, float y) const -> void
{
    if (text)
        TTF_DrawRendererText(text.get(), x, y);
}

auto TextRenderer::size(const Text& text) -> SDL_Point
{
    SDL_Point size{};
    if (text)
        TTF_GetTextSize(text.get(), &size.x, &size.y);
    return size;
}
