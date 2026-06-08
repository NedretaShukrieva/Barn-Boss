#pragma once
#include <string>
#include "GameException.h"

enum class ProductType {
    WheatSeed = 1,
    CornSeed,
    Chicken,
    Cow,
    Wheat,
    Corn,
    Egg,
    Milk
};

namespace Utils
{
    std::string productTypeToString(ProductType type);

    ProductType stringToProductType(const std::string& s);

    int toIndex(ProductType type);
    
};

