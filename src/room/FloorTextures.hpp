#pragma once

#include <array>
#include <cstddef>
#include <string_view>

#include "Tile.hpp"

namespace FloorTextures
{
    struct Entry
    {
        FloorType type;
        std::string_view path;
    };

    inline constexpr std::array entries
    {
        Entry{FloorType::Wood, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_WoodLight.png"},
        Entry{FloorType::Stone, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_Stone.png"},
        Entry{FloorType::ArmyGreen, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_ArmyGreen.png"},
        Entry{FloorType::BeigeYellow, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_BeigeYellow.png"},
        Entry{FloorType::Black, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_Black.png"},
        Entry{FloorType::Blue, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_Blue.png"},
        Entry{FloorType::BlueLight, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_BlueLight.png"},
        Entry{FloorType::BlueSea, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_BlueSea.png"},
        Entry{FloorType::Bone, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_Bone.png"},
        Entry{FloorType::BrightBlue, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_BrightBlue.png"},
        Entry{FloorType::BrokenWhite, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_BrokenWhite.png"},
        Entry{FloorType::BrownDark, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_BrownDark.png"},
        Entry{FloorType::BrownLight, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_BrownLight.png"},
        Entry{FloorType::CheckBoardBig, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_CheckBoardBig.png"},
        Entry{FloorType::Checkboard, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_Checkboard.png"},
        Entry{FloorType::ClassyBlue, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_ClassyBlue.png"},
        Entry{FloorType::ClassyRed, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_ClassyRed.png"},
        Entry{FloorType::Concrete, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_Concrete.png"},
        Entry{FloorType::Dark, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_Dark.png"},
        Entry{FloorType::DarkBlue, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_DarkBlue.png"},
        Entry{FloorType::Green, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_Green.png"},
        Entry{FloorType::Indigo, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_Indigo.png"},
        Entry{FloorType::Japan1, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_Japan_1.png"},
        Entry{FloorType::Japan2, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_Japan_2.png"},
        Entry{FloorType::Love, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_Love.png"},
        Entry{FloorType::Natural, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_Natural.png"},
        Entry{FloorType::Old, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_Old.png"},
        Entry{FloorType::Orange, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_Orange.png"},
        Entry{FloorType::Purple, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_Purple.png"},
        Entry{FloorType::Red, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_Red.png"},
        Entry{FloorType::Sea, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_Sea.png"},
        Entry{FloorType::Serious, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_Serious.png"},
        Entry{FloorType::Sky, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_Sky.png"},
        Entry{FloorType::Traditional, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_Traditional.png"},
        Entry{FloorType::UnsatRed, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_UnsatRed.png"},
        Entry{FloorType::Violet, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_Violet.png"},
        Entry{FloorType::White, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_White.png"},
        Entry{FloorType::WhiteCheck, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_WhiteCheck.png"},
        Entry{FloorType::WoodBright, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_WoodBright.png"},
        Entry{FloorType::WoodHard, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_WoodHard.png"},
        Entry{FloorType::WoodLight, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_WoodLight.png"},
        Entry{FloorType::Yellow, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_128_Yellow.png"},
        Entry{FloorType::Bathroom1, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_Bath_1(128).png"},
        Entry{FloorType::Bathroom2, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Floor_Bath_2(128).png"},
        Entry{FloorType::Lab1, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_64/Floor_64_Lab_1.png"},
        Entry{FloorType::Lab2, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_64/Floor_64_Lab_2.png"},
        Entry{FloorType::Lab3, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_64/Floor_64_Lab_3.png"},
        Entry{FloorType::Lab4, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_64/Floor_64_Lab_4.png"},
        Entry{FloorType::Lab5, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_64/Floor_64_Lab_5.png"},
        Entry{FloorType::Japanese, "assets/pixel_salvaje/themed_sets/Japanese_Room/Floor_Japanese_128.png"},
        Entry{FloorType::Shower, "assets/pixel_salvaje/themed_sets/Bathroom/Shower_Floor.png"},
    };

    [[nodiscard]] constexpr auto pathFor(FloorType type) -> std::string_view
    {
        return entries[static_cast<std::size_t>(type)].path;
    }
}
