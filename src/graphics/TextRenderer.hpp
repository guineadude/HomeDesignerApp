#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <map>
#include <memory>
#include <string>
#include <string_view>

struct TextEngineDeleter
{
    void operator()(TTF_TextEngine* engine) const
    {
        TTF_DestroyRendererTextEngine(engine);
    }
};

struct FontDeleter
{
    void operator()(TTF_Font* font) const
    {
        TTF_CloseFont(font);
    }
};

struct TextDeleter
{
    void operator()(TTF_Text* text) const
    {
        TTF_DestroyText(text);
    }
};

using Text = std::unique_ptr<TTF_Text, TextDeleter>;

class TextRenderer
{
public:
    [[nodiscard]] auto init(SDL_Renderer* renderer, std::string_view fontPath) -> bool;
    auto shutdown() -> void;

    [[nodiscard]] auto createText(std::string_view string, float pointSize, SDL_Color color) -> Text;
    auto draw(const Text& text, float x, float y) const -> void;

    //helper for text size
    [[nodiscard]] static auto size(const Text& text) -> SDL_Point;

private:
    // helper to get font at size
    [[nodiscard]] auto font(float pointSize) -> TTF_Font*;

    std::unique_ptr<TTF_TextEngine, TextEngineDeleter> m_engine;
    std::map<float, std::unique_ptr<TTF_Font, FontDeleter>> m_fonts;
    std::string m_fontPath;
};
