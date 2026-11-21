#pragma once

#include "ui/elements/ScrollBar.hpp"
#include "ui/elements/Window.hpp"
#include "ui/elements/Button.hpp"
#include "ui/elements/Label.hpp"
#include "ui/elements/Image.hpp"
#include <variant>
#include <vector>

using UIElement = std::variant<Window, ScrollBar, Button, Label, Image>;

struct UIWrapper
{
    std::vector<UIElement> elements;
    std::size_t zOrder {}; // default z-order
    bool visible {true};
};