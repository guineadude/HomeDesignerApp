#pragma once

#include "UI_Elements/ScrollBar.hpp"
#include "UI_Elements/Window.hpp"
#include "UI_Elements/Button.hpp"
#include "UI_Elements/Label.hpp"
#include "UI_Elements/Image.hpp"
#include <variant>
#include <vector>

using UIElement = std::variant<Window, ScrollBar, Button, Label, Image>;

struct UIWrapper
{
    std::vector<UIElement> elements;
    std::size_t zOrder {}; // default z-order
    bool visible {true};
};