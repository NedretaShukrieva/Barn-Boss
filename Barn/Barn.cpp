#include "Barn.h"
#include <print>
#include <fstream>
#include "GameException.h"


void Barn::addProduct(ProductType type, unsigned int quantity)
{
    inventory[Utils::toIndex(type)] += quantity;
}

bool Barn::removeProduct(ProductType type, unsigned int quantity)
{
    int idx = Utils::toIndex(type);

    if (inventory[idx] < quantity) {
        std::println("Not enough quantity!");
        return false;
    }

    inventory[idx] -= quantity;
    return true;
}

unsigned int Barn::getQuantity(ProductType type) const
{
    return inventory[Utils::toIndex(type)];
}

void Barn::display() const
{
    for (int i = 1; i < COUNT; i++) {
        ProductType type = static_cast<ProductType>(i);
        std::println("{}: {}", Utils::productTypeToString(type), inventory[i]);
    }
}


std::ostream& operator<<(std::ostream& os, const Barn& barn)
{
    os << "BARN\n";

    for (int i = 1; i < COUNT; i++) {
        if (barn.inventory[i] > 0) {
            ProductType type = static_cast<ProductType>(i);
            os << Utils::productTypeToString(type)
                << " " << barn.inventory[i] << "\n";
        }
    }

    os << "END\n";
    return os;
}

std::istream& operator>>(std::istream& is, Barn& barn)
{
    std::string token;
    is >> token; 

    if (token != "BARN")
        throw InvalidFileFormatException();

    std::string typeStr;
    while (is >> typeStr && typeStr != "END") {
        unsigned int qty;
        is >> qty;

        ProductType type = Utils::stringToProductType(typeStr);
        barn.inventory[Utils::toIndex(type)] = qty;
    }

    return is;
}
