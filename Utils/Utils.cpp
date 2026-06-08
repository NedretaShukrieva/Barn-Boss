#include "Utils.h"
#include <print>


std::string Utils::productTypeToString(ProductType type)
{
    switch (type) {
    case ProductType::Wheat:     return "Wheat";
    case ProductType::Corn:      return "Corn";
    case ProductType::Egg:       return "Egg";
    case ProductType::Milk:      return "Milk";
    case ProductType::WheatSeed: return "WheatSeed";
    case ProductType::CornSeed:  return "CornSeed";
    case ProductType::Chicken:   return "Chicken";
    case ProductType::Cow:       return "Cow";
    }

    throw InvalidProductException();
}


ProductType Utils::stringToProductType(const std::string& s)
{
    if (s == "Wheat") return ProductType::Wheat;
    if (s == "Corn") return ProductType::Corn;
    if (s == "Egg") return ProductType::Egg;
    if (s == "Milk") return ProductType::Milk;
    if (s == "WheatSeed") return ProductType::WheatSeed;
    if (s == "CornSeed") return ProductType::CornSeed;
    if (s == "Chicken") return ProductType::Chicken;
    if (s == "Cow") return ProductType::Cow;

    std::println("Unknown product: '{}'", s);

    throw InvalidProductException();
    
}

int Utils::toIndex(ProductType type)
{
    int index = (int)type;

    if (index < 1 || index > 8)
        throw InvalidProductException();

    return index;
}
