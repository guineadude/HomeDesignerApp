#include "debug/Debug.hpp"

#include <cstddef>

#include "furniture/FurnitureCatalogue.hpp"

namespace Catalogue
{
    namespace Debug
    {
        namespace
        {
            std::size_t furnitureIndex{};
        }

        auto cycleFurnitureCatalogue(const FurnitureCatalogue& catalogue) -> void
        {
            furnitureIndex = (furnitureIndex + 1) % catalogue.size();

            Core::Debug::log(
                "Selected furniture: ",
                catalogue.getDefinitionAt(furnitureIndex).name
            );
        }

        auto getCurrentFurnitureDefinition(const FurnitureCatalogue& catalogue) -> const FurnitureDefinition&
        {
            return catalogue.getDefinitionAt(furnitureIndex);
        }
    }
}
