#pragma once

#include <vector>
#include <cstddef>

#include "FurnitureDefinition.hpp"
#include "debug.hpp"


namespace DEBUG_vars
{
    inline std::size_t furnitureIndex {};
    inline FurnitureDefinition currentFurniture {};
}

class FurnitureCatalogue 
{
public:
        FurnitureCatalogue() { // TODO remove this debug when no longer needed
            DEBUG_vars::furnitureIndex = 0;
            DEBUG_vars::currentFurniture = furnitureDefinitions[0];
        };
private:
    
    enum class UnlockStatus { Purchased, Locked }; // will be used for progress later
    std::vector<FurnitureDefinition> furnitureDefinitions {
        FurnitureDefinition{ "Wooden Bed", "textures/wooden_bed.png", 2, 1, 100, {0, 0} },
        FurnitureDefinition{ "Wooden Cupboard", "textures/wooden_cupboard.png", 1, 2, 150, {0, 0} },
        FurnitureDefinition{ "Bedside Table", "textures/bedside_table.png", 1, 1, 50, {0, 0} },
        FurnitureDefinition{ "Wooden Table", "textures/wooden_table.png", 2, 2, 200, {0, 0} },
        FurnitureDefinition{ "Potted Plant", "textures/potted_plant.png", 1, 1, 30, {0, 0} }
    };    
public:
    auto DEBUG_cycleFurnitureCatalogue() -> FurnitureDefinition&
    {
        DEBUG_vars::currentFurniture = furnitureDefinitions[DEBUG_vars::furnitureIndex++ % furnitureDefinitions.size()];
        debug::log(DEBUG_vars::currentFurniture.name.c_str());
        return DEBUG_vars::currentFurniture;
    }
    auto DEBUG_getCurrentFurnitureDefintion() -> FurnitureDefinition& { return DEBUG_vars::currentFurniture; }
};  