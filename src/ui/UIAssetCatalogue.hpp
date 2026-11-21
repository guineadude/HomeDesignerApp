#pragma once

#include <string>
#include <vector>
#include <SDL3/SDL.h>


enum UIAssetUniqueID
{
    // --- 16x16 sprite sheets ---
    UI_Gamepad_16,
    UI_Style1_16,
    UI_Style2_16,

    // --- 32x32 sprite sheets ---
    UI_Gamepad_32,
    UI_Style1_32,
    UI_Style2_32,

    // --- 48x48 sprite sheets ---
    UI_Gamepad_48,
    UI_Style1_48,
    UI_Style2_48,

    // --- 16x16 animated trash button frames ---
    UI_TrashAnim_16_1,
    UI_TrashAnim_16_2,
    UI_TrashAnim_16_3,
    UI_TrashAnim_16_4,
    UI_TrashAnim_16_5,
    UI_TrashAnim_16_6,

    // --- 32x32 animated trash button frames ---
    UI_TrashAnim_32_1,
    UI_TrashAnim_32_2,
    UI_TrashAnim_32_3,
    UI_TrashAnim_32_4,
    UI_TrashAnim_32_5,
    UI_TrashAnim_32_6,

    // --- 48x48 animated trash button frames ---
    UI_TrashAnim_48_1,
    UI_TrashAnim_48_2,
    UI_TrashAnim_48_3,
    UI_TrashAnim_48_4,
    UI_TrashAnim_48_5,
    UI_TrashAnim_48_6,

    UI_AssetCount
};

struct UIAsset
{
    UIAssetUniqueID UniqueID;
    std::string sheetPath;
    SDL_FRect sourceRect{};
};


class UIAssetCatalogue
{
public:

    auto getAssetPaths() const -> const std::vector<UIAsset>& { return assetPaths; }
    auto getAssetByID(UIAssetUniqueID id) const -> const UIAsset* ;
    auto getAssetByPath(const std::string& path) const -> const UIAsset* ;

    const std::vector<UIAsset> assetPaths
    {
        // --- 16x16 sprite sheets ---
        { UI_Gamepad_16, "assets/UI/16x16/Modern_UI_Gamepad.png" },
        { UI_Style1_16,  "assets/UI/16x16/Modern_UI_Style_1.png" },
        { UI_Style2_16,  "assets/UI/16x16/Modern_UI_Style_2.png" },

        // --- 32x32 sprite sheets ---
        { UI_Gamepad_32, "assets/UI/32x32/Modern_UI_Gamepad_32x32.png" },
        { UI_Style1_32,  "assets/UI/32x32/Modern_UI_Style_1_32x32.png" },
        { UI_Style2_32,  "assets/UI/32x32/Modern_UI_Style_2_32x32.png" },

        // --- 48x48 sprite sheets ---
        { UI_Gamepad_48, "assets/UI/48x48/Modern_UI_Gamepad_48x48.png" },
        { UI_Style1_48,  "assets/UI/48x48/Modern_UI_Style_1_48x48.png" },
        { UI_Style2_48,  "assets/UI/48x48/Modern_UI_Style_2_48x48.png" },

        // --- 16x16 animated trash button frames ---
        { UI_TrashAnim_16_1, "assets/UI/16x16/Animated/Modern_UI_Button_Trash_1.gif" },
        { UI_TrashAnim_16_2, "assets/UI/16x16/Animated/Modern_UI_Button_Trash_2.gif" },
        { UI_TrashAnim_16_3, "assets/UI/16x16/Animated/Modern_UI_Button_Trash_3.gif" },
        { UI_TrashAnim_16_4, "assets/UI/16x16/Animated/Modern_UI_Button_Trash_4.gif" },
        { UI_TrashAnim_16_5, "assets/UI/16x16/Animated/Modern_UI_Button_Trash_5.gif" },
        { UI_TrashAnim_16_6, "assets/UI/16x16/Animated/Modern_UI_Button_Trash_6.gif" },

        // --- 32x32 animated trash button frames ---
        { UI_TrashAnim_32_1, "assets/UI/32x32/Animated_32x32/Modern_UI_Button_Trash_32x32_1.gif" },
        { UI_TrashAnim_32_2, "assets/UI/32x32/Animated_32x32/Modern_UI_Button_Trash_32x32_2.gif" },
        { UI_TrashAnim_32_3, "assets/UI/32x32/Animated_32x32/Modern_UI_Button_Trash_32x32_3.gif" },
        { UI_TrashAnim_32_4, "assets/UI/32x32/Animated_32x32/Modern_UI_Button_Trash_32x32_4.gif" },
        { UI_TrashAnim_32_5, "assets/UI/32x32/Animated_32x32/Modern_UI_Button_Trash_32x32_5.gif" },
        { UI_TrashAnim_32_6, "assets/UI/32x32/Animated_32x32/Modern_UI_Button_Trash_32x32_6.gif" },

        // --- 48x48 animated trash button frames ---
        { UI_TrashAnim_48_1, "assets/UI/48x48/Animated_48x48/Modern_UI_Button_Trash_48x48_1.gif" },
        { UI_TrashAnim_48_2, "assets/UI/48x48/Animated_48x48/Modern_UI_Button_Trash_48x48_2.gif" },
        { UI_TrashAnim_48_3, "assets/UI/48x48/Animated_48x48/Modern_UI_Button_Trash_48x48_3.gif" },
        { UI_TrashAnim_48_4, "assets/UI/48x48/Animated_48x48/Modern_UI_Button_Trash_48x48_4.gif" },
        { UI_TrashAnim_48_5, "assets/UI/48x48/Animated_48x48/Modern_UI_Button_Trash_48x48_5.gif" },
        { UI_TrashAnim_48_6, "assets/UI/48x48/Animated_48x48/Modern_UI_Button_Trash_48x48_6.gif" },
    };
};
