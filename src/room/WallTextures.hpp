#pragma once

#include <array>
#include <cstddef>
#include <string_view>

#include "room/Tile.hpp"

namespace WallTextures
{
    struct Entry
    {
        WallType type {};
        std::string_view leftPath {}; // for east walls
        std::string_view rightPath {}; // for north walls
    };

    inline constexpr std::array entries
    {
        Entry{WallType::Brick, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_Brick.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_Brick.png"},
        Entry{WallType::Concrete, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_Concrete.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_Concrete.png"},
        Entry{WallType::ArmyGreen, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_ArmyGreen.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_ArmyGreen.png"},
        Entry{WallType::BeigeYellow, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_BeigeYellow.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_BeigeYellow.png"},
        Entry{WallType::Black, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_Black.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_Black.png"},
        Entry{WallType::BlueLight, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_BlueLight.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_BlueLight.png"},
        Entry{WallType::BlueSea, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_BlueSea.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_BlueSea.png"},
        Entry{WallType::Bone, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_Bone.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_Bone.png"},
        Entry{WallType::BrightBlue, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_BrightBlue.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_BrightBlue.png"},
        Entry{WallType::BrokenWhite, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_BrokenWhite.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_BrokenWhite.png"},
        Entry{WallType::BrownLight, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_BrownLight.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_BrownLight.png"},
        Entry{WallType::Checkboard, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_Checkboard.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_Checkboard.png"},
        Entry{WallType::ClassyBlue, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_ClassyBlue.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_ClassyBlue.png"},
        Entry{WallType::ClassyRed, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_ClassyRed.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_ClassyRed.png"},
        Entry{WallType::Dark, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_Dark.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_Dark.png"},
        Entry{WallType::DarkBlue, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_DarkBlue.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_DarkBlue.png"},
        Entry{WallType::Green, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_Green.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_Green.png"},
        Entry{WallType::Indigo, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_Indigo.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_Indigo.png"},
        Entry{WallType::Japan1, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_Japan_1.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_Japan_1.png"},
        Entry{WallType::Japan2, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_Japan_2.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_Japan_2.png"},
        Entry{WallType::Love, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_Love.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_Love.png"},
        Entry{WallType::Natural, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_Natural.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_Natural.png"},
        Entry{WallType::Old, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_Old.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_Old.png"},
        Entry{WallType::Orange, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_Orange.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_Orange.png"},
        Entry{WallType::Purple, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_Purple.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_Purple.png"},
        Entry{WallType::Red, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_Red.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_Red.png"},
        Entry{WallType::Sea, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_Sea.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_Sea.png"},
        Entry{WallType::Serious, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_Serious.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_Serious.png"},
        Entry{WallType::Sky, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_Sky.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_Sky.png"},
        Entry{WallType::Stone, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_Stone.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_Stone.png"},
        Entry{WallType::Traditional, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_Traditional.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_Traditional.png"},
        Entry{WallType::UnsatRed, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_UnsatRed.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_UnsatRed.png"},
        Entry{WallType::Violet, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_Violet.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_Violet.png"},
        Entry{WallType::White, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_White.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_White.png"},
        Entry{WallType::WhiteCheck, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_WhiteCheck.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_WhiteCheck.png"},
        Entry{WallType::WoodBright, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_WoodBright.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_WoodBright.png"},
        Entry{WallType::WoodHard, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_WoodHard.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_WoodHard.png"},
        Entry{WallType::WoodLight, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_WoodLight.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_WoodLight.png"},
        Entry{WallType::Yellow, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_L_128_Yellow.png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_R_128_Yellow.png"},
        Entry{WallType::Bathroom1, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_Bath_1(128).png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_Bath_1(128).png"},
        Entry{WallType::Bathroom2, "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_Bath_2(128).png", "assets/pixel_salvaje/environment/Floor_Wall_Tiles_128/Wall_Bath_2(128).png"},
        Entry{WallType::Debug, "assets/debug/DevWallEast.png", "assets/debug/DevWallNorth.png"}
    };

    [[nodiscard]] constexpr auto leftPathFor(WallType type) -> std::string_view
    {
        return entries[static_cast<std::size_t>(type)].leftPath;
    }

    [[nodiscard]] constexpr auto rightPathFor(WallType type) -> std::string_view
    {
        return entries[static_cast<std::size_t>(type)].rightPath;
    }
}