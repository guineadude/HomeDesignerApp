#pragma once

#include <map>
#include "ui/UIWrapper.hpp"
#include "graphics/TextRenderer.hpp"
#include "debug/Debug.hpp"

namespace UI
{
    using WrapperKey = std::pair<std::size_t, std::string>;
}

class UIManager
{
public:


    auto init(int windowHeight, int windowWidth, SDL_Renderer* renderer, TextRenderer& textRenderer) -> bool
    {
        try
        {
        // --- catalogue panel: window + title ---
        UIWrapper cataloguePanelWrapper {};
            
            constexpr std::string_view buttonTexturePath {"assets/UI/16x16/Modern_UI_Style_1.png"};
            constexpr float windowPanelMargin {6.0f};
            constexpr float windowPanelWidth  {300.0f};
            const SDL_FRect windowPanelBounds {
                .x = static_cast<float>(windowWidth) - windowPanelWidth - windowPanelMargin,
                .y = windowPanelMargin,
                .w = windowPanelWidth,
                .h = static_cast<float>(windowHeight) - (windowPanelMargin * 2.0f),
            };

            constexpr UI::NineSlice windowPanelNineSlice { .left = 6.0f, .right = 6.0f, .top = 6.0f, .bottom = 6.0f, .scale = 4.0f };

            cataloguePanelWrapper.elements.emplace_back(std::in_place_type<Window>,
                WindowConfig{
                    .position    = SDL_FPoint{ .x = windowPanelBounds.x, .y = windowPanelBounds.y },
                    .bounds      = windowPanelBounds,
                    .sourceRect  = SDL_FRect{ .x = 58.0f, .y = 129.0f, .w = 28.0f, .h = 29.0f },
                    .texturePath = std::string{buttonTexturePath},
                    .onClick     = []{},
                    .nineSlice   = windowPanelNineSlice,
                },
                renderer);
            cataloguePanelWrapper.zOrder = 0;
            cataloguePanelWrapper.visible = false;

            constexpr float titleTopPadding {16.0f};
            constexpr float titleHeight     {48.0f};
            cataloguePanelWrapper.elements.emplace_back(std::in_place_type<Label>,
                LabelConfig{
                    .text      = "Catalogue",
                    .pointSize = 30.0f,
                    .color     = SDL_Color{58, 58, 80, 255},
                    .centerIn  = SDL_FRect{
                        .x = windowPanelBounds.x,
                        .y = windowPanelBounds.y + titleTopPadding,
                        .w = windowPanelBounds.w,
                        .h = titleHeight,
                    },
                },
                textRenderer);
            cataloguePanelWrapper.zOrder = 0;
            cataloguePanelWrapper.visible = false;

            // --- catalogue scroll bar: right edge of the panel, below the title ---
            // sprites are 5x18 px with a 1px border, so the track can stretch to any height
            constexpr UI::NineSlice scrollBarNineSlice { .left = 1.0f, .right = 1.0f, .top = 1.0f, .bottom = 1.0f, .scale = 4.0f };
            constexpr float scrollBarWidth   {5.0f * scrollBarNineSlice.scale};
            constexpr float thumbHeight      {18.0f * scrollBarNineSlice.scale};
            constexpr float panelBorder      {windowPanelNineSlice.right * windowPanelNineSlice.scale};
            constexpr float scrollBarGap     {8.0f};                     // same gap on right, top and bottom
            const float trackTop    { windowPanelBounds.y + titleTopPadding + titleHeight + scrollBarGap };
            const float trackBottom { windowPanelBounds.y + windowPanelBounds.h - panelBorder - scrollBarGap };
            const SDL_FRect trackBounds {
                .x = windowPanelBounds.x + windowPanelBounds.w - panelBorder - scrollBarGap - scrollBarWidth,
                .y = trackTop,
                .w = scrollBarWidth,
                .h = trackBottom - trackTop,
            };
            constexpr SDL_FRect thumbNormalSource  { .x = 309.0f, .y = 79.0f, .w = 5.0f, .h = 18.0f }; // light
            constexpr SDL_FRect thumbHoveredSource { .x = 325.0f, .y = 79.0f, .w = 5.0f, .h = 18.0f }; // mid
            constexpr SDL_FRect thumbPressedSource { .x = 325.0f, .y = 79.0f, .w = 5.0f, .h = 18.0f }; // mid
            constexpr SDL_FRect trackSource        { .x = 341.0f, .y = 79.0f, .w = 5.0f, .h = 18.0f }; // dark
            cataloguePanelWrapper.elements.emplace_back(std::in_place_type<ScrollBar>,
                ScrollBarConfig{
                    .thumbBounds      = SDL_FRect{ .x = trackBounds.x, .y = trackBounds.y,
                                                   .w = scrollBarWidth, .h = thumbHeight },
                    .trackBounds      = trackBounds,
                    .m_onScroll       = []{},
                    .thumbTexturePath = std::string{buttonTexturePath},
                    .trackTexturePath = std::string{buttonTexturePath},
                    .sources          = {
                        .normal  = thumbNormalSource,
                        .hovered = thumbHoveredSource,
                        .pressed = thumbPressedSource,
                    },
                    .trackSource      = trackSource,
                    .nineSlice        = scrollBarNineSlice,
                },
                renderer);

            addWrapper("cataloguePanel", 0, std::move(cataloguePanelWrapper));

        // --- catalogue button: the cart button on its own ---
        UIWrapper catalogueButtonWrapper {};
            
            constexpr float cartButtonScale {4.0f};
            constexpr SDL_FRect cartNormalSource  { .x = 864.0f, .y = 271.0f, .w = 16.0f, .h = 17.0f };
            constexpr SDL_FRect cartHoveredSource { .x = 880.0f, .y = 271.0f, .w = 16.0f, .h = 17.0f };
            constexpr SDL_FRect cartPressedSource { .x = 896.0f, .y = 271.0f, .w = 16.0f, .h = 17.0f };
            catalogueButtonWrapper.elements.emplace_back(std::in_place_type<Button>,
                ButtonConfig{
                    .position    = SDL_FPoint{ .x = 6.0f, .y = 6.0f },
                    .bounds      = SDL_FRect{ .x = 16.0f, .y = 16.0f,
                                            .w = cartNormalSource.w * cartButtonScale,
                                            .h = cartNormalSource.h * cartButtonScale },
                    .onClick     = { [&]{ toggleWrapper("cataloguePanel");
                                        toggleWrapper("catalogueLabel"); } },
                    .texturePath = std::string{buttonTexturePath},
                    .sources     = {
                        .normal  = cartNormalSource,
                        .hovered = cartHoveredSource,
                        .pressed = cartPressedSource,
                    },
                },
                renderer);
            catalogueButtonWrapper.zOrder = 0;
            catalogueButtonWrapper.visible = true;
                
            addWrapper("catalogueButton", 0, std::move(catalogueButtonWrapper));
        }
        catch (const std::exception& e)
        {
            Core::Debug::log("Failed to create button: ", e.what());
            return false;
        }
        return true;
    }    
    
    auto addWrapper(const std::string& name, std::size_t z, UIWrapper w) -> void 
        { m_wrappers.emplace(UI::WrapperKey{z, name}, std::move(w)); }

    [[nodiscard]] auto getWrapper(const std::string& name) const -> const UIWrapper*;
    [[nodiscard]] auto getWrapper(const std::string& name) -> UIWrapper*;
    
    auto renderWrappers(SDL_Renderer* renderer) const -> void;
    auto toggleWrapper(const std::string& name) -> void;

    auto handleHover(const SDL_MouseMotionEvent& e) -> void;
    auto handleMouseButton(const SDL_MouseButtonEvent& e) -> void;
    
    auto clear() -> void 
        { m_wrappers.clear(); }
private:

    std::map<UI::WrapperKey, UIWrapper> m_wrappers {};
};