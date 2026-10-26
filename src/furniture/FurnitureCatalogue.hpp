#pragma once

#include <cstddef>
#include <vector>

#include "FurnitureDefinition.hpp"
#include "debug.hpp"

class FurnitureCatalogue
{
public:
    [[nodiscard]]
    auto size() const -> std::size_t
    {
        return furnitureDefinitions.size();
    }

    [[nodiscard]]
    auto getDefinition(std::size_t index) const -> const FurnitureDefinition&
    {
        return furnitureDefinitions.at(index);
    }

private:
    std::vector<FurnitureDefinition> furnitureDefinitions{
        {"Wooden Bed", "textures/wooden_bed.png", {2, 1}, 100, {0, 0}},
        {"Wooden Cupboard", "textures/wooden_cupboard.png", {1, 2}, 150, {0, 0}},
        {"Bedside Table", "textures/bedside_table.png", {1, 1}, 50, {0, 0}},
        {"Wooden Table", "textures/wooden_table.png", {2, 2}, 200, {0, 0}},
        {"Potted Plant", "textures/potted_plant.png", {1, 1}, 30, {0, 0}}
    };
};

namespace DEBUG
{
    inline std::size_t furnitureIndex{};

    inline auto getCurrentFurnitureDefinition(const FurnitureCatalogue& catalogue) -> const FurnitureDefinition&
    {
        return catalogue.getDefinition(furnitureIndex);
    }

    inline auto cycleFurnitureCatalogue(const FurnitureCatalogue& catalogue) -> const FurnitureDefinition&
    {
        furnitureIndex = (furnitureIndex + 1) % catalogue.size();

        const auto& definition { getCurrentFurnitureDefinition(catalogue) };
        debug::log(definition.name.c_str());

        return definition;
    }
}