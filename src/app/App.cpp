#include "app.hpp"

#include "SDL3/SDL_events.h"
#include "debug.hpp"

auto App::init() -> bool
{
    if(!SDL_Init(SDL_INIT_VIDEO))
    {
        Core::Debug::log("SDL_Init failed: ", SDL_GetError());
        return false;
    }

    m_isVideoInitialised = true;
    m_window = SDL_CreateWindow(
        "Home Designer Focus App",
        windowWidth,
        windowHeight,
        SDL_WINDOW_RESIZABLE
    );

    if(!m_window)
    {
        Core::Debug::log("SDL_CreateWindow failed: ", SDL_GetError());
        return false;
    }

    if(!TTF_Init())
    {
        Core::Debug::log("TTF_Init failed: ", SDL_GetError());
        return false;
    }
    m_isTTFInitialised = true;

    m_renderer = SDL_CreateRenderer(m_window, nullptr);
    if(!m_renderer)
    {
        Core::Debug::log("SDL_CreateRenderer failed: ", SDL_GetError());
        return false;
    }

    if(!SDL_SetRenderVSync(m_renderer, vsyncRefreshInterval))
    {
        Core::Debug::log("SDL_SetRenderVSync failed: ", SDL_GetError());
        return false;
    }

    if(!m_textRenderer.init(m_renderer, fontPath))
    {
        Core::Debug::log("Failed to initialise text renderer");
        return false;
    }

    if(!m_roomScene.loadTextures(m_renderer))
    {
        Core::Debug::log("Failed to load textures");
        return false;
    }

    try
    {
        // --- catalogue panel: window + title ---
        UIWrapper cataloguePanelWrapper {};


        constexpr float windowPanelMargin {16.0f};
        constexpr float windowPanelWidth  {400.0f};
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
            m_renderer);
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
            m_textRenderer);
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
            m_renderer);

        m_uiManager.addWrapper("cataloguePanel", 0, std::move(cataloguePanelWrapper));

        // --- catalogue button: the cart button on its own ---
        UIWrapper catalogueButtonWrapper {};
        
        constexpr float cartButtonScale {4.0f};
        constexpr SDL_FRect cartNormalSource  { .x = 864.0f, .y = 271.0f, .w = 16.0f, .h = 17.0f };
        constexpr SDL_FRect cartHoveredSource { .x = 880.0f, .y = 271.0f, .w = 16.0f, .h = 17.0f };
        constexpr SDL_FRect cartPressedSource { .x = 896.0f, .y = 271.0f, .w = 16.0f, .h = 17.0f };
        catalogueButtonWrapper.elements.emplace_back(std::in_place_type<Button>,
            ButtonConfig{
                .position    = SDL_FPoint{ .x = 16.0f, .y = 64.0f },
                .bounds      = SDL_FRect{ .x = 16.0f, .y = 64.0f,
                                          .w = cartNormalSource.w * cartButtonScale,
                                          .h = cartNormalSource.h * cartButtonScale },
                .onClick     = { [&]{ m_uiManager.toggleWrapper("cataloguePanel");
                                      m_uiManager.toggleWrapper("catalogueLabel"); } },
                .texturePath = std::string{buttonTexturePath},
                .sources     = {
                    .normal  = cartNormalSource,
                    .hovered = cartHoveredSource,
                    .pressed = cartPressedSource,
                },
            },
            m_renderer);
        catalogueButtonWrapper.zOrder = 0;
        catalogueButtonWrapper.visible = true;
            
        m_uiManager.addWrapper("catalogueButton", 0, std::move(catalogueButtonWrapper));
    }
    catch (const std::exception& e)
    {
        Core::Debug::log("Failed to create button: ", e.what());
        return false;
    }
    

    return true;
}

auto App::handleEvent(const SDL_Event& event) -> SDL_AppResult
{
    //handle app events
    if(event.type == SDL_EVENT_QUIT
        || (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE))
        return SDL_APP_SUCCESS;

    //if click, try handle UI
    if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN || event.type == SDL_EVENT_MOUSE_BUTTON_UP)
        m_uiManager.handleMouseButton(SDL_MouseButtonEvent{event.button});
    if(event.type == SDL_EVENT_MOUSE_MOTION)
        m_uiManager.handleHover(SDL_MouseMotionEvent{event.motion});
    //handle room scene events
    m_roomScene.handleEvent(event);

    return SDL_APP_CONTINUE;
}

auto App::update() -> SDL_AppResult
{
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    SDL_RenderClear(m_renderer);

    m_roomScene.update();
    m_roomScene.render(m_renderer);
    m_roomScene.renderUI(m_renderer, m_uiManager);
    
    SDL_RenderPresent(m_renderer);

    return SDL_APP_CONTINUE;
}

auto App::shutdown() -> void
{
    // UI owns textures and TTF_Text objects, so it must go before the text engine and renderer
    m_uiManager.clear();
    m_roomScene.shutdown();
    m_textRenderer.shutdown();
    if(m_renderer)
    {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
    if(m_window)
    {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
    if(m_isTTFInitialised)
    {
        TTF_Quit();
        m_isTTFInitialised = false;
    }
    if(m_isVideoInitialised)
    {
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        m_isVideoInitialised = false;
    }
}