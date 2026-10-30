#pragma once

#include <cstddef>
#include <vector>

#include "FurnitureDefinition.hpp"
#include "debug.hpp"

class FurnitureCatalogue
{
public:
    [[nodiscard]] auto size() const -> std::size_t
    {
        return m_furnitureDefinitions.size();
    }
    [[nodiscard]] auto getDefinition(std::size_t index) const -> const FurnitureDefinition&
    {
        return m_furnitureDefinitions.at(index);
    }

private:
    std::vector<FurnitureDefinition> m_furnitureDefinitions{
        {FurnitureUniqueID::WoodenBed,"Wooden Bed","assets/pixel_salvaje/themed_sets/Bedroom/Bed_E_4.png",{1,2},100, {-78.0f, -49.0f}, 0.9f},       
        {FurnitureUniqueID::BedsideTable, "Bedside Table", "assets/pixel_salvaje/themed_sets/Bedroom/Night_Table_Tile.png", {1, 1}, 50, {-29.0f, -32.0f}},
        {FurnitureUniqueID::WoodenTable, "Wooden Table", "assets/pixel_salvaje/furniture/Tables/Table_10.png", {1, 1}, 200, {-58.0f, -82.0f}},
        {FurnitureUniqueID::WoodenCupboard, "Wooden Cupboard", "assets/pixel_salvaje/themed_sets/Office/Office_Wood_Closet_Ani/Office_Wood_Closet.png", {1, 1}, 150, {-78.0f, -49.0f}},
        {FurnitureUniqueID::PottedPlant, "Potted Plant", "assets/pixel_salvaje/decorations/Plants/Plant_1.png", {1, 1}, 30, {-78.0f, -49.0f}}
    };
};

namespace Catalogue
{
    namespace Debug
    {
        inline std::size_t furnitureIndex{};

        inline auto cycleFurnitureCatalogue(const FurnitureCatalogue& catalogue) -> void
        {
            furnitureIndex = (furnitureIndex + 1) % catalogue.size();

            Core::Debug::log(
                "Selected furniture: ",
                catalogue.getDefinition(furnitureIndex).name
            );
        }
        [[nodiscard]] inline auto getCurrentFurnitureDefinition(const FurnitureCatalogue& catalogue) -> const FurnitureDefinition&
        {
            return catalogue.getDefinition(furnitureIndex);
        }   
    }
}   